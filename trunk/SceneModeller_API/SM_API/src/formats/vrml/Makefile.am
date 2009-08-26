lib_LTLIBRARIES = libvrml1++.la

BISON = bison

# Compile the parser and save cycles.
# This code comes from "Handling Tools that Produce Many Outputs",
# from the Automake documentation.
EXTRA_DIST = $(srcdir)/vrml1-parser.stamp $(srcdir)/vrml1-parser.yy
# Don't depend on $(BISON) otherwise we would rebuild these files
# in srcdir, including during distcheck, which is forbidden.
$(srcdir)/vrml1-parser.stamp: $(srcdir)/vrml1-parser.yy
	@rm -f vrml1-parser.tmp
	@touch vrml1-parser.tmp
	$(BISON) -d -ra -S lalr1.cc -o $(srcdir)/vrml1-parser.cc $(srcdir)/vrml1-parser.yy
	@mv -f vrml1-parser.tmp $@

$(libvrml1_sources_generated): $(srcdir)/vrml1-parser.stamp
	@if test -f $@; then :; else \
		rm -f $(srcdir)/vrml1-parser.stamp && \
		$(MAKE) $(AM_MAKEFLAGS) $(srcdir)/vrml1-parser.stamp; \
	fi

libvrml1_sources_generated = \
        $(srcdir)/stack.hh $(srcdir)/position.hh $(srcdir)/location.hh \
        $(srcdir)/vrml1-parser.hh $(srcdir)/vrml1-parser.cc


VRML1_RELEASE=${VERSION}
VRML1_LIBRARY_VERSION=0:0:0
#                     | | |
#              +------+ | +---+
#              |        |     |
#           current:revision:age
#              |        |     |
#              |        |     +- increment if interfaces have been added
#              |        |        set to zero if interfaces have been removed
#              |        |        or changed
#              |        +- increment if source code has changed
#              |           set to zero if current is incremented
#              +- increment if interfaces have been added, removed or changed

libvrml1___la_LDFLAGS= -version-info $(VRML1_LIBRARY_VERSION) -release $(VRML1_RELEASE)


libvrml1_release_headers = Driver.hh Separator.hh Document.hh Attribute.hh Cube.hh Node.hh SubStack.hh Cone.hh USE.hh Switch.hh Sphere.hh Cylinder.hh SFColor.hh Material.hh MaterialBinding.hh Translation.hh SFVec3f.hh SFRotation.hh Rotation.hh Scale.hh SFMatrix.hh MatrixTransform.hh Transform.hh OrthographicCamera.hh PerspectiveCamera.hh PointLight.hh SpotLight.hh DirectionalLight.hh SFVec2f.hh Texture2Transform.hh ShapeHints.hh NormalBinding.hh FontStyle.hh LOD.hh Normal.hh Coordinate3.hh TextureCoordinate2.hh PointSet.hh IndexedLineSet.hh IndexedFaceSet.hh Texture2.hh SFImage.hh WWWInline.hh WWWAnchor.hh AsciiText.hh vrml1-parser.hh stack.hh location.hh position.hh
libvrml1_headers = convert.hh ${libvrml1_release_headers}

libvrml1_sources = Document.cc Attribute.cc Cube.cc Node.cc SubStack.cc Driver.cc Separator.cc Cone.cc USE.cc Switch.cc Sphere.cc Cylinder.cc SFColor.cc Material.cc MaterialBinding.cc Translation.cc SFVec3f.cc SFRotation.cc Rotation.cc Scale.cc SFMatrix.cc MatrixTransform.cc Transform.cc  OrthographicCamera.cc PerspectiveCamera.cc PointLight.cc SpotLight.cc DirectionalLight.cc SFVec2f.cc Texture2Transform.cc ShapeHints.cc NormalBinding.cc FontStyle.cc LOD.cc Normal.cc Coordinate3.cc TextureCoordinate2.cc PointSet.cc IndexedLineSet.cc IndexedFaceSet.cc Texture2.cc SFImage.cc WWWInline.cc WWWAnchor.cc AsciiText.cc 

libvrml1___la_SOURCES = $(libvrml1_sources_generated) vrml1-scanner.ll $(libvrml1_headers) $(libvrml1_sources)

library_includedir=$(includedir)/libvrml1++-${VRML1_RELEASE}/libvrml1++
library_include_HEADERS = $(libvrml1_release_headers)

