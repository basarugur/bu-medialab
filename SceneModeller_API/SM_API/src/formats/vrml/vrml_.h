/**
 * @doc EXTERNAL VRML
 * 
 * @module VRML.H - VRML 1.x Scene Graph |
 * This file defines the needed structures to handle VRML 1.x scene graph.
 *
 * @rem This library fully complies with VRML 1.x specification (I think)
 *
 * This library heavily uses RTTI for dynamic creation of objects (it creates the
 * different <c CVRMLValue>s through RTTI and <mf CRuntimeClass::CreateObject> function).
 *
 * The main class is <c CVRMLScene>, where resides the VRML file parsing and loading 
 * capabilities. All the other classes define the structure needed to traverse the built 
 * scene graph (and do whatever you want with it). 
 *
 * The design of the parser is based in SGI's VRML 2.x parser, which is one of the simplest and smartest 
 * things I've seen on the matter: The parser only knows about simple types of VRML (SFxxxx and MFxxxx) 
 * and definition nodes, and knows nothing about the nodes themselves. Then it loads a library of default 
 * nodes (defined in a totally compliant VRML file, which has the peculiarity that it only defines nodes 
 * and not instances of them), and presto!, you are ready to load any VRML 1.x compliant file. 
 * The included file allnodes.wrl is that library of standard VRML 1.x nodes. The normal operation is to 
 * load that library as if it was a normal VRML file (and it IS!), so standard nodes get defined, and then 
 * load your desired VRML file/s (you can load as many VRML files as you want in the same scene). 
 *
 * The error detecting capabilities of this class are quite weak, it only returns FALSE if file is invalid, 
 * and I wouldn't find it strange if it hanged with corrupt VRML files :-m. 
 *
 * The parser has two non-stantard properties: the VRML file needn't to be a unique VRML node (there 
 * are plenty of VRML files that have more than one root node), and any node (and not only group nodes) 
 * can have children nodes. The latter is a side effect of not knowing beforehand the standard nodes (anyway, 
 * this is VRML 1.x standard's fault, because user defined nodes can't mark in any way if they have children 
 * nodes or not ... VRML 1.x is quite a dumb language, if I may say it: it's not LALR, and some hacks are 
 * needed to parse it with Bison). 
 * 
 * @author atejada@bancamarch.es | Antonio Tejada Lacaci
 * 
 * @update 2000-2-03 | ATL | Example added
 * @update 2000-1-31 | ATL | Some thoughts on DEF and USE nodes added.
 * Added field <md CVRMLNodeType::m_pvrntDef>. 
 * DEF and USE nodes are supported, although untested.
 * @update 2000-1-26 | ATL | Deallocation routines added
 * @update 1999-3-31 | ATL | Creation
 *  
 * @todo Fill <mf CVRMLValue::SetValue>s conversion between compatible <c CVRMLValue>s descendants
 * @todo Polish up documentation 
 * @todo Some arrays of pointers to objects could be done with arrays of scalars, general structure 
 * could be more C-style instead of C++ style
 * @todo Use <mf CArray::DestroyElements> template functions instead <mf CVRMLValue::Destroy>
 * @todo Check that when deleting NodeTypes, references of DEF NodeTypes are not lost
 * @todo Enhance error checking capabilities

 * @ex To load the VRML file myscene.wrl just do |
 * 
 * CVRMLScene vrscn;
 * // The default VRML 1.x node library must be loaded first
 * // in order the default node types to be defined
 * vrscn.LoadScene("allnodes.wrl");
 * // Load the desired scene
 * vrscn.LoadScene("myscene.wrl");
 * 
 * @ex To traverse the instance nodes of a  <c CVRMLScene> do |
// This function traverses a node, all its fields and childs
void TraverseNode(CVRMLNode* pvrn) {
   // Name of this node
   pvrn->m_strName;
   // Type of this node
   CVRMLNodeType* pvrnt = pvrn->m_pvrntType;
   // Name of the type of this node
   pvrnt->m_strName;
   // Now we could access any attributes of the type of this node 
   // (declared fields, default values...) read CVRMLNodeType class to get an idea

   // Traverse each FieldValue (pairs of CVRMLFieldType + CVRMLValue), 
   // this is, the values for each field (CVRMLValue) and 
   // information on its type and name (CVRMLFieldType)
   // Only present in instance nodes for fields with non-default value 
   // in this instance node (defined fields in .wrl file)
   // You have to access to CVRMLFieldType to get the default value.
   for (int j=0;j<pvrn->m_vrfvValues.GetSize();j++) {
      // FieldValue for this field
      CVRMLFieldValue* pvrfv = pvrn->m_vrfvValues[j];
      // The value is in
      pvrfv->m_pvrvValue;
      // The field type is in
      CVRMLFieldType* pvrft = pvrfv->m_pvrftType;
      // Now we can access the type information for this field
      // The name of this field is
      pvrft->m_strName;
      // And the type of the value stored in this field is
      pvrft->m_pvrtType;
      // while the default value for this field is
      pvrft->m_pvrvValue;
   }
   // Traverse each child in the same manner
   for (int i=0;i<pvrn->m_vrnChildren.GetSize();i++) 
      TraverseChild(m_vrnChildren[i]);
}
// This function traverses all the instance nodes in a scene
void TraverseScene(CVRMLScene* pvrsc) {
   for (int i=0;i<pvrsc->m_vrnNodes.GetSize();i++)
      TraverseNode(pvrsc->m_vrnNodes[i]);
}
 *
 * @devnote Still have to workout why flex's buffer isn't deallocated automatically when EOF is reached :-?, 
 * by now this is solved adding a line to vrml1.l matching EOF and deallocating it there, but 
 * I don't think this is a standard solution :-?
 */


#pragma once 
#include <afx.h>
#include <AfxTempl.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif

/**
 * @class This class is the common ancestor for VRML values of all kinds
 * @base public | CObject
 */
class CVRMLValue : public CObject {
public:
   DECLARE_DYNCREATE(CVRMLValue)

//@access Construction
   /**
    * @cmember,mfunc Creates a generic <c CVRMLValue>
    */
   CVRMLValue() {};
   ~CVRMLValue();


//@access Operations
   /**
    * @cmember,mfunc Returns the name of the type of this value
    * @@rdesc Name of the type of this <c CVRMLValue>
    */
   const CString GetTypeName() const { return GetRuntimeClass()->m_lpszClassName;};

//@access Overridables
   /**
    * @cmember,mfunc Sets the value for this node. Default implementation just outputs 
    * a debug string
    * @@parm Value to set this node to
    */
   virtual void SetValue(const CVRMLValue& vrv) {
      TRACE("Casting from %s to %s", vrv.GetTypeName(), this->GetTypeName());
   };
   
//@access Debug
   /**
    * @cmember,mfunc Dumps the contents of the <c CVRMLValue>
    */
   virtual const CString Dump() const {
      CString str;
	  char *charPnt = NULL ;
	  sprintf(charPnt,"VRMLValue instead of %s ",GetTypeName());
      str= charPnt;
      return str;
   };
};


class CSFFloat;
class CSFVec3f;
class CSFLong;

/**
 * @class Metavalue internal to the parser. Holds possible <c CSFMatrix> or <c CSFImage> value.
 * @base public | CVRMLValue
 */
class CSFVecnf : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CSFVecnf)
//@access Construction
   /**
    * @cmember,mfunc Creates a Simple Field vector
    */
   CSFVecnf();
   /**
    * @cmember,mfunc Destructs the <c CSFVecnf> and frees allocated memory
    */
   ~CSFVecnf();

//@access Operations
   /**
    * @cmember,mfunc Deallocates resources allocated for this <c CSFVecnf>
    */
   void Destroy();
 
//@access Overridables
   /**
    * @cmember,mfunc Sets the value for this node. This value doesn't support this function.
    * @@parm Value to set this node to
    */
   virtual void SetValue(const CVRMLValue& vrv) {
      CVRMLValue::SetValue(vrv);
      TRACE(" unsupported!\n");
   };

//@access Public Data Members
   CArray<CSFFloat*, CSFFloat*> m_vnValues;
};

/**
 * @class Metavalue internal to the parser. Holds empty lists of <c CMFFloat>, <c CMFString>,
 * <c CMFVec2f>, <c CMFVec3f>, <c CMFLong>, <c CMFColor>
 * @base public | CVRMLValue
 */
class CMFEmpty : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CMFEmpty)

//@access Construction
   /**
    * @cmember,mfunc Creates a Multifield empty Vector
    */
   CMFEmpty();
   ~CMFEmpty() { TRACE("Destroying CMFEmpty\n"); };

//@access Overridables
   /**
    * @cmember,mfunc Sets the value for this node. This VRMLValue doesn't support this function
    * @@parm Value to set this node to
    */
   virtual void SetValue(const CVRMLValue& vrv) {
      CVRMLValue::SetValue(vrv);
      TRACE(" unsupported!\n");
   };
};


//VRML Classes

/**
 * @class This class holds VRML SFBitMask values (Simple Field BitMask)
 * @base public | CVRMLValue
 */
class CSFBitMask : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CSFBitMask)
//@access Construction

   /**
    * @cmember,mfunc Creates a default BitMask
    */
   CSFBitMask();
   ~CSFBitMask() { TRACE("Destroying CSFBitMask\n"); };

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFEnum>
    * @@parm Value to set this SFBitMask to 
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Public Data Members
   CStringArray m_strValues;  //@cmember Array of mnemonics conforming this SFBitMask
};

/**
 * @class This class holds VRML SFBool values (Simple Field Boolean)
 * @base public | CVRMLValue
 */
class CSFBool : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CSFBool)

//@access Construction
   /**
    * @cmember,mfunc Creates a default Boolean
    */
   CSFBool();
   ~CSFBool() { TRACE("Destroying CSFBool\n"); };

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFEnum>
    * @@parm Value to set this SFBool to
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Operations
   /**
    * @cmember,mfunc Sets the value of this SFBool to a boolean value
    * @@parm Boolean value to set this SFBool to
    */
   operator =(const BOOL b) { m_bValue = b; };

//@access Public Data Members
   BOOL m_bValue; //@cmember Boolean value of this SFBool
   
};

/**
 * @class Holds VRML SFEnum values (Simple Field Enumerations)
 * @base public | CVRMLValue
 */
class CSFEnum : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CSFEnum)

//@access Construction
   /**
    * @cmember,mfunc  Creates a default Simple Field Enumeration 
    */
   CSFEnum();
   ~CSFEnum() { TRACE("Destroying CSFEnum\n"); };

//@access Overridables
   /**
    * @cmember,mfunc Only supports conversion from <c CSFEnum>
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Operations
   /**
    * @cmember,mfunc Sets this SFEnum to the given value
    * @@parm String to set this SFEnum to
    */
   void operator =(const CString& str) { m_strValue = str; };

//@access Public Data Members
   CString m_strValue;  //@cmember Value of this SFEnum
};

/**
 * @class Holds VRML SFFloat values
 * @base public | CVRMLValue
 */
class CSFFloat : public CVRMLValue  {
public:
   DECLARE_DYNCREATE(CSFFloat)

//@access Construction
   /** 
    * @cmember,mfunc Constructs an empty <c CSFFloat>
    */
   CSFFloat();
   CSFFloat(const CSFFloat& sf);
   CSFFloat(const CSFLong& sl);

   ~CSFFloat() { TRACE("Destroying CSFFloat\n"); };

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFLong> to <c CSFFloat>
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Operations
   /**
    * @cmember,mfunc Returns the value of this <c CSFFLoat> as a double
    * @@rdesc The value of this <c CSFFloat> as a double 
    */
   operator double () { return m_dValue; };
   /**
    * @cmember,mfunc Converts from double to <c CSFFLoat>
    * @@parm Double to set this <c CSFFloat> to
    * @@rdesc This <c CSFFloat> with its value set to <p d>
    */
   const CSFFloat& operator =(double d) { 
      m_dValue = d; 
      return *this; 
   };
//@access Debugging
   /**
    * @cmember,mfunc Dumps information about this <c CSFFLoat>
    */
   virtual const CString Dump() const {
      CString str;
	  char *charpnt = NULL;
	  sprintf(charpnt,"%f",m_dValue);
      str = charpnt;
      return str;
   };

//@access Public Data Members
   double m_dValue; //@cmember Value of this <c CSFFloat> as a double
};

/**
 * @class Holds VRML SFImage values
 * @base public | CVRMLValue
 */
class CSFImage : public CVRMLValue  {
public:
   DECLARE_DYNCREATE(CSFImage)

//@access Construction
   /** 
    * @cmember,mfunc Constructor
    */
   CSFImage();
   /**
    * @cmember,mfunc Destructor. Frees the bitmap
    */
   ~CSFImage();

//@access Operations
   /**
    * @cmember,mfunc Converts from <c CSFVecnf> to <c CSFImage>
    */
   const CSFImage& operator =(const CSFVecnf& vrvn);

//@access Overridables
   virtual void SetValue(const CVRMLValue& vrv) {
      CVRMLValue::SetValue(vrv);
      TRACE(" unsupported!\n");
   };

//@access Public Data Members
   DWORD m_dwWidth;        //@cmember Image width
   DWORD m_dwHeight;       //@cmember Image height
   DWORD m_dwBitsPerPixel; //@cmember Bits per pixel
   DWORD *m_dwBits;        //@cmember Image bitmap
};

/**
 * @class Holds VRML SFLong values
 * @base public | CVRMLValue
 */
class CSFLong : public CVRMLValue  {
public:
   DECLARE_DYNCREATE(CSFLong)

//@access Construction

   CSFLong();
   CSFLong(long l) { m_dwValue = l; };
   CSFLong(const CSFLong& sl) { SetValue(sl); };
   CSFLong(const CSFFloat& sf) { SetValue(sf); };

   ~CSFLong() { TRACE("Destroying CSFLong\n"); };

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFFloat> to <c CSFLong>
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Debugging
   virtual const CString Dump() const {
      CString str;
	  char *charpnt = NULL;
	  sprintf(charpnt,"%d",m_dwValue);
      str = charpnt;
      return str;
   };

//@access Operations

   operator DWORD () { return m_dwValue; };
   operator =(const DWORD dw) {
      m_dwValue = dw;
      return *this;
   };

//@access Public Data Members
   DWORD m_dwValue;  //@cmember Value of this <c CSFLong> as a doubleword
};

/**
 * @class Holds VRML SFMatrix values
 * @base public | CVRMLValue
 */
class CSFMatrix : public CVRMLValue  {
public:
   DECLARE_DYNCREATE(CSFMatrix)

//@access Construction
   CSFMatrix();
   ~CSFMatrix() { TRACE("Destroying CSMatrix\n"); };

//@access Overridables
   virtual void SetValue(const CVRMLValue& vrv) {
      CVRMLValue::SetValue(vrv);
      TRACE(" unsupported!\n");
   };

//@access Operations
   operator =(const CSFVecnf& vrvn);

//@access Public Data Members
   double m_dRowCol[4][4];   //@cmember Matrix in row major order 
};

/**
 * @class Holds VRML SFRotation values
 * @base public | CVRMLValue
 */
class CSFRotation : public CVRMLValue  {
public:
   DECLARE_DYNCREATE(CSFRotation)

//@access Construction
   CSFRotation();
   ~CSFRotation() { TRACE("Destroying CSFRotation\n"); };

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFVecnf> to <c CSFRotation>
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Operations
   operator =(const CSFVecnf& vrvn);

//@access Public Data Members
   double m_dAxisX;  //@cmember X component of rotation axis
   double m_dAxisY;  //@cmember Y component of rotation axis
   double m_dAxisZ;  //@cmember Z component of rotation axis
   double m_dAngle;  //@cmember Angle to rotate in radians
};

/**
 * @class Holds VRML SFString values
 * @base public | CVRMLValue
 */
class CSFString : public CVRMLValue  {
public:
   DECLARE_DYNCREATE(CSFString)

//@access Construction
   /**
    * @cmember,mfunc Creates a <c CSFString> empty or from a CString
    */
   CSFString();
   CSFString(const CString str) {
      m_strValue = str;
   }
   /** 
    * @cmember,mfunc Destructs a <c CSFString>
    */
   ~CSFString() { TRACE("Destroying CSFString\n"); };

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFString>
    * @@parm <c CVRMLValue> to set this <c CSFString> to
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Operations
   void operator =(const CString& str) { m_strValue = str; };

//@access Public Data Members
   CString m_strValue;  //@cmember Value of this <c CSFString>
};

/**
 * @class Holds VRML SFVec2f values
 * @base public | CVRMLValue
 */
class CSFVec2f : public CVRMLValue  {
public:
   DECLARE_DYNCREATE(CSFVec2f)

//@access Construction
   /**
    * @cmember Default constructor
    */
   CSFVec2f();
   ~CSFVec2f() { TRACE("Destroying CSFVec2f"); };

//@cmember Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFVecnf> to <c SFVec2f>
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Operations

   operator =(const CSFVecnf& vrvn);

//@access Public Data Members
   double m_dValues[2]; ///@cmember Components of this vector
};

/**
 * @class Holds VRML SFVec3f values
 * @base public | CVRMLValue
 */
class CSFVec3f : public CVRMLValue  {
public:
   DECLARE_DYNCREATE(CSFVec3f)

//@access Construction
   CSFVec3f();
   CSFVec3f(const CSFVec3f& sfv3f) {
      memcpy(m_dValues, sfv3f.m_dValues, sizeof(m_dValues));
   };
   CSFVec3f(const CSFVecnf& sfvnv) {
      SetValue(sfvnv);
   }

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFVecnf>
    * @@parm <c CVRMLValue> to set this <c CSFVec3f> to
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Debugging
   virtual const CString Dump() const {
      CString str;
	  char *charpnt = NULL;
	  sprintf(charpnt,"%f %f %f", m_dValues[0], m_dValues[1], m_dValues[2]);
      str = charpnt;
      return str;
   };

//@access Operations
   operator =(const CSFVecnf& vrvn);

//@access Public Data Members
   double m_dValues[3]; //@cmember Values of each component
};

/**
 * @class Holds VRML SFColor values
 * @base public | CVRMLValue
 */

class CSFColor : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CSFColor)

   CSFColor(const double dRed=0, const double dGreen=0, const double dBlue=0);
   ~CSFColor() { TRACE("Destroying CSFColor"); };

   virtual void SetValue(const CVRMLValue& vrv) {
      CVRMLValue::SetValue(vrv);
      if (vrv.IsKindOf(RUNTIME_CLASS(CSFVecnf))) {
         CSFVecnf* pvnf = (CSFVecnf*) &vrv;
         *this = *pvnf;
         TRACE(" supported!\n");
      } else
         TRACE(" unsupported!\n");
   };
   virtual const CString Dump() const {
      CString str;
	  char *charpnt = NULL;
	  sprintf(charpnt,"%f %f %f",m_dRed, m_dGreen, m_dBlue);
      str = charpnt;
      
      return str;
   };

   const CSFColor& operator =(const CSFVecnf& vrvn);

   double m_dRed;
   double m_dGreen;
   double m_dBlue;
};

/**
 * @class Holds VRML MFColor values (Multi Field Color)
 * @base public | CVRMLValue
 */
class CMFColor : public CVRMLValue {
   
public:
   DECLARE_DYNCREATE(CMFColor)
      
//@access Construction

   /**
    * @cmember,mfunc Creates a default <c CMFColor>
    */
   CMFColor();
   /** 
    * @cmember,mfunc Frees memory allocated for <md CMFColor::m_vcValues>
    */
   ~CMFColor();

//@access Overridables

   /**
    * @cmember,mfunc Allows conversion from <c CSFVecnf> of dimension 3
    * @@parm Value to convert from. 
    */
   virtual void SetValue(const CVRMLValue& vrv) {
      CVRMLValue::SetValue(vrv);
      if (vrv.IsKindOf(RUNTIME_CLASS(CSFVecnf))) {
         CSFVecnf* pvnf = (CSFVecnf*) &vrv;
         TRACE(" supported!\n");
         CSFColor* pvsfc = new CSFColor();
         *pvsfc = *pvnf;
         m_vcValues.Add(pvsfc);
      } else
         TRACE(" unsupported!\n");
      
      //for (int i=0;i<vrmf3f.m_v3Values.GetSize();i++)
      //   m_v3Values.Add(vrmf3f.m_v3Values[i]);*/
   };

//@access Debugging

   /**
    * @cmember,mfunc Returns a string representation of this value
    * @@rdesc Information on this value
    */
   virtual const CString Dump() const {
      CString str="";
      
      for (int i=0;i<m_vcValues.GetSize();i++)
         str += m_vcValues[i]->Dump();
      
      return str;
   };

//@access Public Data Members
   //@cmember Array of the colors that build this <c MFColor>
   CArray<CSFColor*, CSFColor*> m_vcValues;
};

/**
 * @class Holds VRML MFFloat values
 * @base public | CVRMLValue
 */
class CMFFloat : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CMFFloat)

//@access Construction
   /**
    * @cmember Constructs an empty <c CMFFloat>
    */
   CMFFloat();
   /**
    * @cmember Calls <mf CMFFloat::Destroy> and destructs this <c CMFFloat> 
    */
   ~CMFFloat();

//@access Operations
   /**
    * @cmember Deallocates this <c CMFFloat>
    */
   void Destroy();

//@access Debugging
   /**
    * @cmember,mfunc Outputs a string representation of this <c CMFFloat>
    */
   virtual const CString Dump() const {
      CString str="";
      
      for (int i=0;i<m_vfValues.GetSize();i++)
         str += m_vfValues[i]->Dump() + ", ";
      return str;
   };

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFFloat>, <c CSFLong>, <c CMFLong> and  <c CMFEmpty> to <c CMFFloat>
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Public Data Members
   CArray<CSFFloat*, CSFFloat*> m_vfValues; //@cmember SFFloat values
};

/**
 * @class Holds VRML MFLong values
 * @base public | CVRMLValue
 */
class CMFLong  : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CMFLong)

//@access Construction
   /**
    * @cmember Constructs an empty <c CMFLong>
    */
   CMFLong();
   /**
    * @cmember Destructs this <c CMFLong> and deallocates its resources
    */
   ~CMFLong();
  
//@access Debugging
   /**
    * @cmember Returns a <c CString> representation of this <c CMFLong>
    */
   virtual const CString Dump() const {
      CString str="";
      for (int i=0;i<m_vlValues.GetSize();i++)
         str += m_vlValues[i]->Dump() + ", ";
      return str;
   };

//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFFloat>, <c CSFLong> and <c CMFEmpty> 
    * to <c CMFLong>
    * @@parm <c CVRMLValue> to set this value to
    */
   virtual void SetValue(const CVRMLValue& vrv);
   
//@access Public Data Members
   CArray<CSFLong*, CSFLong*> m_vlValues; ///@cmember Array of <c CSFLong> values
};

/**
 * @class Holds VRML MFVec2f values
 * @base public | CVRMLValue
 */
class CMFVec2f : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CMFVec2f)

//@access Construction
   /**
    * @cmember Constructs an empty <c CMFVec2f>
    */
   CMFVec2f();
   /** 
    * @cmember Destructs this <c CMFVec2f>
    */
   ~CMFVec2f();
   
//@access Overridables
   /**
    * @cmember,mfunc This <c CVRMLValue> doesn't support conversions yet.
    */
   virtual void SetValue(const CVRMLValue& vrv) {
      CVRMLValue::SetValue(vrv);
      TRACE(" unsupported!\n");
   };

//@access Public Data Members
   CArray<CSFVec2f*, CSFVec2f*> m_v2Values;  //@cmember Array of <c CSFVec2f> values
};

/**
 * @class Holds VRML MFVec2f values
 * @base public | CVRMLValue
 */
class CMFVec3f : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CMFVec3f)

//@access Construcion
   /**
    * @cmember Constructs an empty <c CMFVec3f>
    */
   CMFVec3f();
   /**
    * @cmember Destructs this <c CMFVec3f>
    */
   ~CMFVec3f();
   
//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFVecnf>
    * @@parm <c CVRMLValue> value to set this <c CMFVec3f> to
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Debugging
   /**
    * @cmember,mfunc Returns a <c CString> representation of this <c CMFVec3f>
    * @@rdesc <c CString> Representation of this <c CMFVec3f>
    */
   virtual const CString Dump() const {
      CString str="";
      
      for (int i=0;i<m_v3Values.GetSize();i++)
         str += m_v3Values[i]->Dump() + ", ";
      
      return str;
   };

//@access Public Data Members
   CArray<CSFVec3f*, CSFVec3f*> m_v3Values;  //@cmember Array of <c CSFVec3f> values
};

/**
 * @class Holds VRML MFString values
 * @base public | CVRMLValue
 */
class CMFString : public CVRMLValue {
public:
   DECLARE_DYNCREATE(CMFString)

//@access Construction
   /**
    * @cmember Constructs an empty <c CMFString>
    */
   CMFString();
   /**
    * @cmember Destructs this <c CMFString>
    */
   ~CMFString();
   
//@access Overridables
   /**
    * @cmember,mfunc Supports conversion from <c CSFString> to <c CMFString>
    * @@parm <c CVRMLValue> to set this <c CMFString> to 
    */
   virtual void SetValue(const CVRMLValue& vrv);

//@access Public Data Members
   CArray<CSFString*, CSFString*> m_vsValues;   //@cmember Array of <c CSFString> values
};

/**
 * @class Contains type information for definitions of VRML nodes.
 * @rem This class is used to store type information and default value for a field of a
 * <c CVRMLNode>.
 *
 * It allows dynamic creation of field values by using RTTI.
 */
class CVRMLFieldType {
public:
//@access Construction
   /**
    * @cmember Constructs an empty <c CVRMLFieldType>
    */
   CVRMLFieldType();
   CVRMLFieldType(const CVRMLFieldType& vrft);
   /**
    * @cmember Destructs this <c CVRMLFieldType> freeing the default value
    * <md CVRMLFieldType::m_pvrvValue>
    */
   ~CVRMLFieldType();

//@access Public Data Members
   CString m_strName;        /// @cmember Name of the field 
   CVRMLValue* m_pvrvValue;  /// @cmember Pointer to default <c CVRMLValue> for this field
   CRuntimeClass* m_pvrtType;/** @cmember Pointer to <c CVRMLValue> class RTTI to create 
                                 fields of this value */
};

/**
 * @class Array of <c CVRMLFieldType>
 */
class CVRMLFieldTypes : public CArray<CVRMLFieldType*, CVRMLFieldType*> {
public:
//@access Construction
   /**
    * @cmember,mfunc Constructor
    */
   CVRMLFieldTypes();
   /**
    * @cmember,mfunc Destructor. Frees the allocated memory for the array
    */
   ~CVRMLFieldTypes();

//@access Operations
   /**
    * @cmember,mfunc Retrieves the <c CVRMLFieldType> of the field with given name
    * @@parm Name of the field whose type we want to retrieve
    * @@rdesc <c VRMLFieldType> with given name
    */
   CVRMLFieldType* GetNamed(const CString& strFieldName) const;
};

/**
 * @class Value for a VRML node field. Contains field type information <c CVRMLFieldType> and
 * its actual value <c CVRMLValue> for a field of a node in a <c CVRMLNode>
 */
class CVRMLFieldValue {
public:
//@access Construction
   /** 
    * @cmember,mfunc Constructs the VRMLFieldValue
    */
   CVRMLFieldValue();

   /**
    * @cmember,mfunc Destructs the <c VRMLFieldValue>, deallocating only the <c CVRMLValue>
    * (the <c CVRMLFieldType> is theoretically owned by a <c CVRMLNodeLib>rary)
    */
   ~CVRMLFieldValue();

//@access Public Data Members
   CVRMLValue* m_pvrvValue;    /** @cmember Pointer to <c CVRMLValue> class containing field's 
                                    VRML value */
   CVRMLFieldType* m_pvrftType;/** @cmember Pointer to <c CVRMLFieldType> with info about 
                                    this field. This <c CVRMLFieldType> is normally owned by a 
                                    <c CVRMLNodeType> in a <c CVRMLNodeLib> */
};

/**
 * @class Array of  <c CVRMLFieldValue>s
 * @base public | CArray
 */
class CVRMLFieldValues : public CArray<CVRMLFieldValue*, CVRMLFieldValue*> {
public:
//@access Construction
   /**
    * @cmember Constructs an empty <c CVRMLFieldValues>
    */
   CVRMLFieldValues();
   /**
    * @cmember Destructs the <c CVRMLFieldValues> and frees its elements
    */
   ~CVRMLFieldValues();
   
//@access Operations
   /**
    * @cmember,mfunc Returns the <c CVRMLFieldValue> of the field named <p strFieldName>
    * @@parm Name of the field whose <c CVRMLFieldValue> we want to retrieve
    * @@rdesc <c CVRMLFieldValue> of the given field
    */
   CVRMLFieldValue* GetNamed(const CString& strFieldName) const;
};

/**
 * @class Placeholder for node type information
 */
class CVRMLNodeType {
public:
//@access Public Data Members
   CVRMLFieldTypes m_vrftTypes;   /** @cmember Types of the fields */
   CString m_strName;             /** @cmember Name of this node type */
   BOOL m_bBuiltin;               /** @cmember true if this is a builtin node (builtin
                                    nodes aren't overriden when redefined) */
   /**
    * @cmember Not NULL if this node is a DEFinition of another node, in which case the 
    * nodes of this type have been instantiated with USE and this node points to the basic node 
    * type or to a chain of DEF NodeTypes ending in a basic (non DEF) node type. 
    */
   CVRMLNodeType* m_pvrntDef;     

//@access Construction
   /**
    * @cmember,mfunc Constructs a <c CVRMLNodeType> and initializes its values
    * @@rem By default it's a no built-in node, with an empty name
    */
   CVRMLNodeType();

//@access Operations
   /**
    * @cmember,mfunc Returns <c CVRMLFieldType> of the field named <p strFieldName>
    * @@rem If this <c CVRMLNodeType> doesn't define that <c CVRMLFieldType>, the chain of 
    * <md CVRMLNodeType::m_pvrntDef> pointers is traversed in search of that <c CVRMLFieldType>
    * and that <c CVRMLFieldType> is returned
    * @@parm Name of the field to retrieve its <c CVRMLFieldType>
    * @@rdesc <c CVRMLFieldType> for field with given name
    * @@xref <mf CVRMLFieldTypes::GetNamed>
    */
   CVRMLFieldType* GetFieldTypeNamed(const CString& strFieldName) const;
};

class CVRMLNodeTypes : public CArray<CVRMLNodeType*, CVRMLNodeType*> {
public:
//@access Construction
   /**
    * @cmember Constructs an empty <c CVRMLNodeType>s array
    */
   CVRMLNodeTypes();
   /**
    * @cmember Destructs this <c CVRMLNodeTypes>
    */
   ~CVRMLNodeTypes();
//@access Operations
   /**
    * @cmember,mfunc Retrieves the <c CVRMLNodeType> of the type of node named <p strNodeName>
    * @@parm Name of the node whose type to retrieve
    * @@rdesc <c CVRMLNodeType> of the node with given name
    */
   CVRMLNodeType* GetNamed(const CString& strNodeName) const ;
};

class CVRMLNode;
/**
 * @class Array of <c CVRMLNode>s
 */
class CVRMLNodes : public CArray<CVRMLNode*, CVRMLNode*> { 
public:
//@access Construction
   /**
    * @cmember Constructs an empty <c CVRMLNodes>
    */
   CVRMLNodes();
   /**
    * @cmember Destructs this <c CVRMLNodes> and frees each of its <c CVRMLNode>
    */
   ~CVRMLNodes();
};

/**
 * @class Placeholder for node instance information
 */
class CVRMLNode {
public:
//@access Construction
   /**
    * @cmember Constructs an empty <c CVRMLNode>
    */
   CVRMLNode();
   /**
    * @cmember Destructs this <c CVRMLNode> and frees allocated resources
    */
   ~CVRMLNode();

//@access Operations
   /**
    * @cmember,mfunc Gets the <c CVRMLValue> for the given field.
    * @@parm Name of the field whose <c CVRMLValue> to retrieve
    * @@rdesc <c CVRMLValue> of the <c CVRMLFieldValue> with given name. 
    * If this node doesn't have a value for this field, the <c CVRMLFieldType>
    * default value of this field is returned.
    * @@devnote If speed is a must, the fallback to <c CVRMLFieldType> default value could be avoided 
    * by creating all the fields of this <c CVRMLNode> in parser time and setting them to default values
    * at the same time, but compatibility could be lost (in theory if a DEFed node is modified
    * all its USErs should be modified).
    */
   CVRMLValue* GetValue(const CString& strFieldName) const;
   CVRMLValue* GetValue(const CVRMLFieldType* pvrft) const;

   /**
    * @cmember,mfunc Gets the <c CVRMLFieldValue> for the given field.
    * @@parm Name of the field whose <c CVRMLFieldValue> to retrieve
    * @@rdesc <c CVRMLValue> of the <c CVRMLFIeldValue> with given name.
    * If this node doesn't have a value for this field, returns NULL
    */
   CVRMLFieldValue* GetFieldValue(const CString& strFieldName) const;

   /**
    * @cmember,mfunc Gets the <c CVRMLFieldType> for the given field.
    * @@parm Name of the field whose <c CVRMLFieldType> to retrieve
    * @@rdesc <c CVRMLFieldType> of the <c CVRMLFieldValue> with given name.
    */
   CVRMLFieldType* GetFieldType(const CString& strFieldName) const;

//@access Public Data Members
   CString m_strName;            //@cmember Name of this instance, maybe empty if not DEF'ed
   CVRMLNodeType* m_pvrntType;   //@cmember Pointer to the library item with info about this node
                                 // This field is normally owned by a <c CVRMLNodeLib>rary
   CVRMLFieldValues m_vrfvValues; //@cmember Fields and values of this node. Values for not present fields
                                 // should be taken from the NodeType library.
   CVRMLNodes m_vrnChildren;     //@cmember Children nodes
};

/**
 * @class Library of VRML Nodes (Built-in + defined)
 * @rem Could be static <c CVRMLNode> thread local information, but just in case. This way you can 
 * have multiple libraries of the same VRML release, multiple libraries of different 
 * releases or both
 *
 * Active node definitions are sought in actual lib array or in builtin child libraries
 * In VRML 1.0, deepest child is returned
 */
class CVRMLNodeLib : public CVRMLNodeTypes {    
public:
//@access Construction
   /**
    * @cmember Constructs an empty <c CVRMLNodeLib>
    */
   CVRMLNodeLib();
   /**
    * @cmember Destructs this <c CVRMLNodeLib> and frees its resources
    */
   ~CVRMLNodeLib() { TRACE("Destroying CVRMLNodeLib\n");};

//@access Public Data Members
   BOOL m_bBuiltIn;  //@cmember True for built-in nodes- mode  
};

/**
 * @class VRML Scene graph
 *
 * A VRML Scene is made of <c CVRMLNodes> and <c CVRMLNodeLib>.
 *
 * When the scene is loaded with LoadScene,
 */
class CVRMLScene {
public:
//@access Construction
   /**
    * @cmember Constructs an empty <c CVRMLScene>
    */
   CVRMLScene();
   /**
    * @cmember Destructs the <c CVRMLScene> and frees all resources allocated to it
    */
   ~CVRMLScene();
//@access Operations
   /**
    * @cmember,mfunc Loads the given scene. Node definitions are read into
    * the node library and node instances are read into the array of <c CVRMLNode>s
    * @@parm Name of the file to load
    * @@rdesc TRUE if the VRML file was loaded successfully
    */
   BOOL LoadScene(CString strFileName);
   BOOL LoadScene(FILE* f);

//@access Public Data Members
   /** 
    * @cmember  List of nodes in this scene. Although VRML 1.x states that an scene is just 
    * one node, there's too much braindead outside that declare VRML files with more than
    * one main node.
    */
   CVRMLNodes m_vrnNodes; 
   CVRMLNodeLib m_vrlLib; //@cmember Library of node types
};

