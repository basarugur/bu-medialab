/*	vrml_io.cpp: implementation
	Authors: Basar Ugur & Isik Baris Fidaner */
#include <iostream>
#include <fstream>
#include "string.h"
#include "vrml_io.h"

#define DONE		0
#define NOT_FOUND  -1

#define SCALE_NORM	4.5
#define MAXCORNER	10
#define STR_MAX		128

bool endsWith(string read, string word)
{
	return (read.length()>=word.length() &&
			read.substr(read.length()-word.length(), word.length()).compare(word)==0);
}

void vrml_io::read(Geometry* g, const char* filename, const char* objectName)
{
	float x, y, z;
	bool ccw = true;
	bool searchObjectName = false, readObject = false, newGeometryRead = false;
	int ch;
	int corners[MAXCORNER], chmax = 20, corner, corner_ctr, iPointsRead = 0;
	string read = "";
	bool coord = false, tex = false;
	bool comment = false;
	FILE *fp;
	float min, max;

	if((fp = fopen(filename,"rb"))==NULL)
		return;

	while( (ch = fgetc(fp)) != EOF)
	{
		read += (char)ch;
		if(read.length() > chmax)
			read = read.substr(1);

		if(read[read.length()-1]=='\n' && comment==true)
			comment = false;

		if(read[read.length()-1]=='#')
			comment = true;

		if(!comment)
		{
			if(endsWith(read,"Coordinate") && !endsWith(read,"TextureCoordinate"))
				coord = true;
			
			if(endsWith(read, "DEF"))
				searchObjectName = true;

			if(searchObjectName && endsWith(read, objectName)) // check if we came across to the objectName
			{
				readObject = true;
				searchObjectName = false; // found, search no more
				// reset geometry:
				g->normals.clear();
				g->points.clear();
				g->vertices.clear();
				g->faces.clear();
			}

			if(endsWith(read, "IndexedFaceSet"))
			{
				newGeometryRead = false;
				ccw = true;
			}

			if(readObject && coord && endsWith(read, "point"))
			{
				iPointsRead = g->points.size();

				while((ch = fgetc(fp))!='[');

				// reading coordinates..	
				do
				{
					while((ch = fgetc(fp))!=']' && (ch<'0' || ch>'9') && ch!='-' && ch!='+');

					if(ch==']')
						break; // end of coordinate list
					else
						fseek(fp,-sizeof(char),SEEK_CUR); // found character, go back one char to read

					fscanf(fp,"%f %f %f",&x,&y,&z);
					Point newPoint(x, y, z);
					Point newNormal(0.0f, 0.0f, 0.0f);
					Vertex newVertex;
					if (g->points.empty()) // extrema stuff
					{
						max = min = y;
						g->pMax = g->pMin = newPoint;
					}
					else
					{
						if (x > g->pMax.x) { g->pMax.x=x; /*if (x>max) max=x;*/ }
						else if (x<g->pMin.x) { g->pMin.x=x; /*if (x<min) min=x;*/ }
						if (y > g->pMax.y)
						{ g->pMax.y=y; if (y>max) max=y;	}
						else if (y < g->pMin.y) { g->pMin.y=y; if (y<min) min=y; }
						if (z > g->pMax.z) { g->pMax.z=z; /*if (z>max) max=z;*/ }
						else if (z < g->pMin.z) { g->pMin.z=z; /*if (z<min) min=z;*/ }
					}

					g->points.push_back(newPoint);
					g->normals.push_back(newNormal);
					g->vertices.push_back(newVertex);

					while((ch = fgetc(fp))!=']' && ch != ',');

				} while(ch == ',');

				coord=false;
			}

			if(readObject && endsWith(read, "ccw"))
			{
				char str[STR_MAX];
				fscanf(fp,"%s",str);

				if(newGeometryRead == false)
				{
					if(strcmp(str,"FALSE")==0)
						ccw=false;
				}
				else
				{
					if(strcmp(str,"FALSE")==0)
						g->invertNormals();
				}
			}

			if(readObject && endsWith(read, "coordIndex"))
			{
				while((ch = fgetc(fp))!='[');

				// reading face corners as point indices
				do
				{
					while((ch = fgetc(fp))!=']' && (ch<'0' || ch>'9'));

					//printf("%c: ",ch);

					if(ch==']') break;
					else fseek(fp,-sizeof(char),SEEK_CUR);

					corner_ctr = 0;
					do
					{
						if(fscanf(fp,"%d%c",&corner, &ch)==EOF)
							break;//exit(2)

						if (corner!=-1)
							corners[corner_ctr++] = corner + iPointsRead;

					} while(corner!=-1);

					// mesh insertions
					// if more than 3 corners, than multiple meshes are inserted accordingly
					for (int i=0; i<corner_ctr-2; i++)
					{
						corners[i]=corners[0];
						Point surfaceNormal = Face::normal(g->points.at(corners[i]), g->points.at(corners[i+1]), g->points.at(corners[i+2]));
						//int newCorners[3];
						for (int j=i;j<i+3;j++)
						{
							g->normals[corners[j]] = g->normals[corners[j]] + surfaceNormal;
							g->vertices[corners[j]].faceIndices.push_back(g->faces.size());
							/*normals.push_back(surfaceNormal);
							vertices.push_back(points[corners[i+j]]);
							newCorners[j] = normals.size() - 1;*/
						}

						Face newFace(&corners[i]);
						g->faces.push_back(newFace);
					}

					while ((char)ch!=']' && (char)ch!=',')
					{
						if((ch = fgetc(fp))==EOF)
							break;//exit(1)
					}

				} while ((char)ch == ',');

				if(ccw==false)
					g->invertNormals();

				newGeometryRead = true;
				readObject = false;
			}
		}

	}

	fclose(fp);
}

void vrml_io::write(Geometry *g, const char* fileName, const char* objectName)
{
	int i;
	FILE *fp = fopen(fileName, "wb");

	fprintf(fp,"#VRML V2.0 utf8\n");
	fprintf(fp,"DEF Mesh-ROOT Transform {\n");
	fprintf(fp,"children [\n");
	fprintf(fp,"  Shape {\n");
	fprintf(fp,"	   appearance Appearance {\n");
	fprintf(fp,"      material Material {\n");
	fprintf(fp,"        diffuseColor 0.5 0.5 0.5\n");
	fprintf(fp,"      }\n");
	fprintf(fp,"    }\n");
	fprintf(fp,"  geometry DEF %s IndexedFaceSet {\n", objectName);
	fprintf(fp,"    ccw TRUE\n");
	fprintf(fp,"    solid TRUE\n");
	fprintf(fp,"    coord DEF Mesh-COORD Coordinate { point [\n");

	//dlg.m_edit1.SetWindowText(_T("Model yaz�l�yor..")); dlg.UpdateWindow();
	for(i=0; i<g->points.size()-1; i++)
	{
		fprintf(fp,"%.6f %.6f %.6f,\n",g->points.at(i).x, g->points.at(i).y, g->points.at(i).z);
		//dlg.m_progress1.SetPos((int)(33 * i / points.size()));
	}
	fprintf(fp,"%.6f %.6f %.6f]\n",g->points.at(i).x, g->points.at(i).y, g->points.at(i).z);

	fprintf(fp,"    }\n");
	fprintf(fp,"    coordIndex [\n");

	//dlg.m_edit1.SetWindowText(_T("Model yaz�l�yor..")); dlg.UpdateWindow();
	for(i=0;i<g->faces.size()-1;i++)
	{
		fprintf(fp,"%d, %d, %d, -1,\n",g->faces.at(i).indices[0], g->faces.at(i).indices[1], g->faces.at(i).indices[2]);
		//dlg.m_progress1.SetPos((int)(33 + 33 * i / faces.size()));
	}
	fprintf(fp,"%d, %d, %d, -1]\n",g->faces.at(i).indices[0], g->faces.at(i).indices[1], g->faces.at(i).indices[2]);

	fprintf(fp,"  }\n");
	fprintf(fp,"}\n");
	fprintf(fp,"]\n");
	fprintf(fp,"}\n");

	fclose(fp);	

	//dlg.m_edit1.SetWindowText(_T("Bitti!")); dlg.UpdateWindow();
	//dlg.DestroyWindow();

}