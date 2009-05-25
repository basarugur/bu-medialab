#include "VRML.h"

extern void yyrestart(FILE* input_file);
extern int yyparse(CVRMLScene* pvrsc);
void yyerror(char *s) {
   TRACE("%s\n",s);
}

IMPLEMENT_DYNCREATE(CVRMLValue, CObject)

CVRMLValue::~CVRMLValue() {
   TRACE("Destroying CVRMLValue of type %s\n", GetRuntimeClass()->m_lpszClassName);
}

IMPLEMENT_DYNCREATE(CSFVecnf, CVRMLValue)
CSFVecnf::CSFVecnf(void) {
    m_vnValues.SetSize(0,1);
}

CSFVecnf::~CSFVecnf() {
   Destroy();
}

void CSFVecnf::Destroy() {
   TRACE("Destroying CSFVecnf\n");
   for (int i=0;i<m_vnValues.GetSize();i++) {
      delete m_vnValues[i];
      m_vnValues[i] = NULL;
   }
   m_vnValues.RemoveAll();
}

IMPLEMENT_DYNCREATE(CMFEmpty, CVRMLValue)
CMFEmpty::CMFEmpty(void) {
}

IMPLEMENT_DYNCREATE(CSFBitMask, CVRMLValue)
CSFBitMask::CSFBitMask(void) {
   m_strValues.SetSize(0,1);
}

void CSFBitMask::SetValue(const CVRMLValue &vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFBitMask))) {
      TRACE(" supported!\n");
      CSFBitMask* psfb = DYNAMIC_DOWNCAST(CSFBitMask, &vrv);
      m_strValues.RemoveAll();
      m_strValues.Append(psfb->m_strValues);
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFEnum))) {
      TRACE(" supported!\n");
      CSFEnum* psfe = DYNAMIC_DOWNCAST(CSFEnum, &vrv);
      m_strValues.RemoveAll();
      m_strValues.Add(psfe->m_strValue);
   } else 
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CSFEnum, CVRMLValue)
CSFEnum::CSFEnum() {
   m_strValue = "";
}

void CSFEnum::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);

   if (vrv.IsKindOf(RUNTIME_CLASS(CSFEnum))) {
      TRACE(" supported!\n");
      CSFEnum* psfe = DYNAMIC_DOWNCAST(CSFEnum, &vrv);
      m_strValue = psfe->m_strValue;
   } else 
      TRACE(" unsupported!\n");
};

IMPLEMENT_DYNCREATE(CSFBool, CVRMLValue)
CSFBool::CSFBool(void) {
   m_bValue = FALSE;
}

void CSFBool::SetValue(const CVRMLValue &vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFBool))) {
      TRACE(" supported!\n");
      CSFBool* psfb = DYNAMIC_DOWNCAST(CSFBool, &vrv);
      m_bValue = psfb->m_bValue;
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFEnum))) {
      TRACE(" supported!\n");
      CSFEnum* psfe = DYNAMIC_DOWNCAST(CSFEnum, &vrv);
      m_bValue = psfe->m_strValue == "TRUE";
   } else
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CSFFloat, CVRMLValue)   
CSFFloat::CSFFloat() {
   m_dValue = 0;
}

CSFFloat::CSFFloat(const CSFFloat& sf) {
   m_dValue = sf.m_dValue;
}

CSFFloat::CSFFloat(const CSFLong& sl) {
   m_dValue = sl.m_dwValue;
}

void CSFFloat::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFFloat))) {
      TRACE(" supported!\n");
      const CSFFloat* psff = DYNAMIC_DOWNCAST(CSFFloat, &vrv);
      m_dValue = psff->m_dValue;
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFLong))) {
      TRACE(" supported!\n");
      const CSFLong* psfl = DYNAMIC_DOWNCAST(CSFLong, &vrv);
      m_dValue = psfl->m_dwValue;
   } else
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CSFColor, CVRMLValue)
CSFColor::CSFColor(double dRed, double dGreen, double dBlue) {
   m_dRed = dRed;
   m_dGreen = dGreen;
   m_dBlue = dBlue;
}
const CSFColor& CSFColor::operator =(const  CSFVecnf& vrvn) {
   ASSERT(3 == vrvn.m_vnValues.GetSize());
   m_dRed = *(vrvn.m_vnValues[0]);
   m_dGreen = *(vrvn.m_vnValues[1]);
   m_dBlue = *(vrvn.m_vnValues[2]);
   return *this;
}

IMPLEMENT_DYNCREATE(CSFImage, CVRMLValue)
CSFImage::CSFImage(void) {
   m_dwWidth = 0;
   m_dwHeight = 0;
   m_dwBitsPerPixel = 0;
   m_dwBits = NULL;
}
const CSFImage& CSFImage::operator =(const CSFVecnf& vrvn) {
   ASSERT(vrvn.m_vnValues.GetSize() >= 3);

   m_dwWidth = (DWORD) ((double) *vrvn.m_vnValues[0]);
   m_dwHeight = (DWORD) ((double) *vrvn.m_vnValues[1]);
   m_dwBitsPerPixel = (DWORD) ((double) *vrvn.m_vnValues[2]);

   ASSERT(((DWORD) vrvn.m_vnValues.GetSize()) == (m_dwWidth * m_dwHeight) + 3);
   m_dwBits = new DWORD[m_dwWidth*m_dwHeight];
   for (DWORD i=0;i<m_dwWidth*m_dwHeight;i++)
      m_dwBits[i] = (DWORD) ((double) *vrvn.m_vnValues[i+3]);
   return *this;
}

CSFImage::~CSFImage() {
   TRACE("Detroying CSFImage\n");
   if (m_dwBits) free(m_dwBits);
   m_dwBits = NULL;
}


IMPLEMENT_DYNCREATE(CSFLong, CVRMLValue)
CSFLong::CSFLong() {
}

void CSFLong::SetValue(const CVRMLValue &vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFLong))) {
      CSFLong* psfl = DYNAMIC_DOWNCAST(CSFLong, &vrv);
      m_dwValue = psfl->m_dwValue; 
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFFloat))) {
      CSFFloat* psff = DYNAMIC_DOWNCAST(CSFFloat, &vrv);
      m_dwValue = (long) *psff; 
   } else 
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CSFMatrix, CVRMLValue)
CSFMatrix::CSFMatrix() {
}

IMPLEMENT_DYNCREATE(CSFRotation, CVRMLValue)
CSFRotation::CSFRotation() {
}

void CSFRotation::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFRotation))) {
      TRACE(" supported!\n");
      CSFRotation* psfr = DYNAMIC_DOWNCAST(CSFRotation, &vrv);
      m_dAxisX = psfr->m_dAxisX;
      m_dAxisY = psfr->m_dAxisY;
      m_dAxisZ = psfr->m_dAxisZ;
      m_dAngle = psfr->m_dAngle;
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFVecnf))) {
      TRACE(" supported!\n");
      CSFVecnf* psfv = DYNAMIC_DOWNCAST(CSFVecnf, &vrv);
      ASSERT(psfv->m_vnValues.GetSize() == 4);
      m_dAxisX = *psfv->m_vnValues[0];
      m_dAxisY = *psfv->m_vnValues[1];
      m_dAxisZ = *psfv->m_vnValues[2];
      m_dAngle = *psfv->m_vnValues[3];
   } else 
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CSFString, CVRMLValue)
CSFString::CSFString() {
}

void CSFString::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFString))) {
      CSFString* psfs = DYNAMIC_DOWNCAST(CSFString, &vrv);
      m_strValue = psfs->m_strValue;
   } else 
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CSFVec2f, CVRMLValue)
CSFVec2f::CSFVec2f() {
}

void CSFVec2f::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFVec2f))) {
      TRACE(" supported!\n");
      CSFVec2f* psfv = DYNAMIC_DOWNCAST(CSFVec2f, &vrv);
      memcpy(m_dValues, psfv->m_dValues, sizeof(m_dValues));
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFVecnf))) {
      TRACE(" supported!\n");
      CSFVecnf* psfv = DYNAMIC_DOWNCAST(CSFVecnf, &vrv);
      ASSERT(psfv->m_vnValues.GetSize() == 2);
      m_dValues[0] = *psfv->m_vnValues[0];
      m_dValues[1] = *psfv->m_vnValues[1];
   } else
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CSFVec3f, CVRMLValue)
CSFVec3f::CSFVec3f() {
}

void CSFVec3f::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFVec3f))) {
      TRACE(" supported!\n");
      CSFVec3f* psfv3 = DYNAMIC_DOWNCAST(CSFVec3f, &vrv);
      memcpy(m_dValues, psfv3->m_dValues, sizeof(m_dValues));
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFVecnf))) {
      TRACE(" supported!\n");
      CSFVecnf* psfvn = DYNAMIC_DOWNCAST(CSFVecnf, &vrv);
      ASSERT(psfvn->m_vnValues.GetSize() == 3);
      for (int i=0;i<3;i++)
         m_dValues[i] = psfvn->m_vnValues[i]->m_dValue;
   } else {
      TRACE(" unsupported!\n");
   }
}

IMPLEMENT_DYNCREATE(CMFColor, CVRMLValue)
CMFColor::CMFColor() {
   m_vcValues.SetSize(0,1);
}

CMFColor::~CMFColor() {
   TRACE("Destroying CMFColor\n");
   for (int i=0;i<m_vcValues.GetSize();i++) {
      delete m_vcValues[i];
      m_vcValues[i] = NULL;
   }
   m_vcValues.RemoveAll();
}

IMPLEMENT_DYNCREATE(CMFFloat, CVRMLValue)
CMFFloat::CMFFloat() {
   m_vfValues.SetSize(0,5);
}

CMFFloat::~CMFFloat() {
   Destroy();
}

void CMFFloat::Destroy() {
   TRACE("Destroying CMFFloat\n");
   for (int i=0;i<m_vfValues.GetSize();i++) {
      delete m_vfValues[i];
      m_vfValues[i] = NULL;
   }
   m_vfValues.RemoveAll();
}

void CMFFloat::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CSFFloat))) {
      TRACE(" supported!\n");
      Destroy();
      CSFFloat* pvsf = new CSFFloat();
      pvsf->SetValue(vrv);
      m_vfValues.Add(pvsf);
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFLong))) {
      TRACE(" supported!\n");
      Destroy();
      const CSFLong* pvsfl = DYNAMIC_DOWNCAST(CSFLong, &vrv);
      m_vfValues.Add(new CSFFloat(*pvsfl));      
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CMFLong))) { 
      TRACE(" supported!\n");
      Destroy();
      const CMFLong* pvmfl = DYNAMIC_DOWNCAST(CMFLong, &vrv);
      for (int i=0;i< pvmfl->m_vlValues.GetSize();i++) {
         m_vfValues.Add(new CSFFloat(*pvmfl->m_vlValues[i]));
      }
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CMFEmpty))) {
      TRACE(" supported!\n");
      Destroy();
   } else
      TRACE(" unsupported!\n");
   
   //for (int i=0;i<vrmf3f.m_v3Values.GetSize();i++)
   //   m_v3Values.Add(vrmf3f.m_v3Values[i]);*/
}

IMPLEMENT_DYNCREATE(CMFLong, CVRMLValue)
CMFLong::CMFLong() {
   m_vlValues.SetSize(0,1);
}

CMFLong::~CMFLong() {
   TRACE("Destroying CMFLong\n");
   for (int i=0;i<m_vlValues.GetSize();i++) {
      delete m_vlValues[i];
      m_vlValues[i] = NULL;
   }
   m_vlValues.RemoveAll();
}

void CMFLong::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CMFLong))) {
      TRACE(" supported!\n");
      for (int j = 0;j<m_vlValues.GetSize();j++) {
         delete m_vlValues[j];
         m_vlValues[j] = NULL;
      }
      m_vlValues.RemoveAll();
      CMFLong* pmfl = DYNAMIC_DOWNCAST(CMFLong, &vrv);
      for (int i=0;i<pmfl->m_vlValues.GetSize();i++)
         m_vlValues.Add(new CSFLong(*m_vlValues[i]));
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CMFFloat))) {
      CMFFloat* pvmf = (CMFFloat*) &vrv;
      TRACE(" supported!\n");
      for (int j = 0;j<m_vlValues.GetSize();j++) {
         delete m_vlValues[j];
         m_vlValues[j] = NULL;
      }
      m_vlValues.RemoveAll();
      for (int i=0;i<pvmf->m_vfValues.GetSize();i++) {
         m_vlValues.Add(new CSFLong((long)((double) *pvmf->m_vfValues[i])));
      }
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFLong))) {
      CSFLong* pvsl = DYNAMIC_DOWNCAST(CSFLong, &vrv);
      TRACE(" supported!\n");
      for (int j = 0;j<m_vlValues.GetSize();j++) {
         delete m_vlValues[j];
         m_vlValues[j] = NULL;
      }
      m_vlValues.RemoveAll();
      m_vlValues.Add(new CSFLong(*pvsl));
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CMFEmpty))) {
      TRACE(" supported!\n");
   } else 
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CMFVec2f, CVRMLValue)
CMFVec2f::CMFVec2f() {
   m_v2Values.SetSize(0,1);
}
CMFVec2f::~CMFVec2f() {
   TRACE("Destroying CMFVec2f\n");
   for (int i=0;i<m_v2Values.GetSize();i++) {
      delete m_v2Values[i];
      m_v2Values[i] = NULL;
   }
   m_v2Values.RemoveAll();
}

IMPLEMENT_DYNCREATE(CMFVec3f, CVRMLValue)
CMFVec3f::CMFVec3f() {
   m_v3Values.SetSize(0,1);
}
CMFVec3f::~CMFVec3f() {
   TRACE("Destroying CMFVec3f\n");
   for (int i=0;i<m_v3Values.GetSize();i++) {
      delete m_v3Values[i];
      m_v3Values[i] = NULL;
   }
   m_v3Values.RemoveAll();
}

void CMFVec3f::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CMFVec3f))) {
      TRACE(" supported!\n");
      CMFVec3f* pv3f = (CMFVec3f*) &vrv;
      for (int j=0;j<m_v3Values.GetSize();j++) {
         delete m_v3Values[j];
         m_v3Values[j] = NULL;
      }
      m_v3Values.RemoveAll();
      for (int i=0;i<pv3f->m_v3Values.GetSize();i++)
         m_v3Values.Add(new CSFVec3f(*pv3f->m_v3Values[i]));
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFVecnf))) {
      TRACE(" supported!\n");
      CSFVecnf* psfv = DYNAMIC_DOWNCAST(CSFVecnf, &vrv);
      for (int j=0;j<m_v3Values.GetSize();j++) {
         delete m_v3Values[j];
         m_v3Values[j] = NULL;
      }
      m_v3Values.RemoveAll();
      m_v3Values.Add(new CSFVec3f(*psfv));
   } else
      TRACE(" unsupported!\n");
}

IMPLEMENT_DYNCREATE(CMFString, CVRMLValue)
CMFString::CMFString() {
   m_vsValues.SetSize(0,1);
}

CMFString::~CMFString() {
   TRACE("Destroying CMFString\n");
   for (int i=0;i<m_vsValues.GetSize();i++) {
      delete m_vsValues[i];
      m_vsValues[i] = NULL;
   }
   m_vsValues.RemoveAll();
}

void CMFString::SetValue(const CVRMLValue& vrv) {
   CVRMLValue::SetValue(vrv);
   if (vrv.IsKindOf(RUNTIME_CLASS(CMFString))) {
      // Conversion from CMFString
      TRACE(" supported!\n");
      const CMFString *pmfs = DYNAMIC_DOWNCAST(CMFString, &vrv);
      m_vsValues.RemoveAll();
      for (int i=0;i<pmfs->m_vsValues.GetSize();i++) m_vsValues.Add(pmfs->m_vsValues[i]);
   } else if (vrv.IsKindOf(RUNTIME_CLASS(CSFString))) {
      // Conversion from CSFString
      TRACE(" supported!\n");
      const CSFString *psfs = DYNAMIC_DOWNCAST(CSFString, &vrv);
      m_vsValues.RemoveAll();
      m_vsValues.Add(new CSFString(psfs->m_strValue));
   } else
      TRACE(" unsupported!\n");
}

CVRMLFieldType::CVRMLFieldType() {
   m_pvrtType = NULL;
   m_pvrvValue = NULL;
   m_strName = "";
}

CVRMLFieldType::CVRMLFieldType(const CVRMLFieldType& vrft) {
   m_strName = vrft.m_strName;
   m_pvrtType = vrft.m_pvrtType;
   m_pvrvValue = vrft.m_pvrvValue;
}

CVRMLFieldType::~CVRMLFieldType() {
   TRACE("Destroying CVRMLFieldType of class %s\n",m_pvrvValue->GetRuntimeClass()->m_lpszClassName);
   delete m_pvrvValue;
   m_pvrtType = NULL;
   m_strName = "";
   m_pvrvValue = NULL;
}

CVRMLFieldValue::CVRMLFieldValue() {
   m_pvrftType = NULL;
   m_pvrvValue = NULL;
}

CVRMLFieldValue::~CVRMLFieldValue() {
   TRACE("Destroying CVRMLFieldValue\n");
   delete m_pvrvValue;
   m_pvrvValue = NULL;
   m_pvrftType = NULL;
}

CVRMLFieldTypes::CVRMLFieldTypes() {
   SetSize(0,1);
}

CVRMLFieldType* CVRMLFieldTypes::GetNamed(const CString& strFieldName) const {
   CVRMLFieldType* pvft;
   for (int i=0;i<GetSize();i++) {
      pvft = GetAt(i);
      if (strFieldName == pvft->m_strName) return pvft;
   }
   pvft = NULL;
   return pvft;
}

CVRMLFieldTypes::~CVRMLFieldTypes() {
   TRACE("Destroying CVRMLFieldTypes\n");
   for (int i=0;i<GetSize();i++) {
      delete ElementAt(i);
      SetAt(i, NULL);
   }
   RemoveAll();
}

CVRMLFieldValues::CVRMLFieldValues() {
   SetSize(0,1);
}

CVRMLFieldValues::~CVRMLFieldValues() {
   TRACE("Destroying CVRMLFieldValues\n");
   for (int i=0;i<GetSize();i++) {
      delete ElementAt(i);
      SetAt(i, NULL);
   }
   RemoveAll();
}

CVRMLFieldValue* CVRMLFieldValues::GetNamed(const CString &strFieldName) const {
   CVRMLFieldValue* pvfv = NULL;
   for (int i=0; ((pvfv == NULL) && (i<GetSize())); i++) {
      if (GetAt(i)->m_pvrftType->m_strName == strFieldName)
         pvfv = GetAt(i);
   }
   return pvfv;
};

CVRMLNodeType::CVRMLNodeType() {
   m_bBuiltin = FALSE;
   m_pvrntDef = NULL;
   m_strName = "";
}

CVRMLFieldType* CVRMLNodeType::GetFieldTypeNamed(const CString& strFieldName) const {
   CVRMLFieldType* pvrft = m_vrftTypes.GetNamed(strFieldName);
   // Search the chain of DEFinitions
   if ((!pvrft) && (m_pvrntDef)) 
      pvrft = m_pvrntDef->GetFieldTypeNamed(strFieldName);
   return pvrft;
}

CVRMLNodeTypes::CVRMLNodeTypes() {
   SetSize(0,1);
}

CVRMLNodeType* CVRMLNodeTypes::GetNamed(const CString& strNodeName) const {
   for (int i=0;i<GetSize();i++)
         if (strNodeName == GetAt(i)->m_strName) return GetAt(i);
   return NULL;
}

CVRMLNodeTypes::~CVRMLNodeTypes() {
   TRACE("Destroying CVRMLNodeTypes\n");
   for (int i=0;i<GetSize();i++) {
      delete ElementAt(i);
      SetAt(i, NULL);
   }
   RemoveAll();
}

CVRMLNode::CVRMLNode() {
   m_strName = "";
   m_pvrntType = NULL;
}

CVRMLNode::~CVRMLNode() {
   TRACE("Destroying CVRMLNode\n");
}

CVRMLValue* CVRMLNode::GetValue(const CString& strFieldName) const {
   CVRMLFieldValue* pvfv = GetFieldValue(strFieldName);
   if (pvfv == NULL) {
      // This node doesn't specify a value for this field, falling to default
      // value in CVRMLFieldType
      return GetFieldType(strFieldName)->m_pvrvValue;
   }
   return pvfv->m_pvrvValue;
}

CVRMLValue* CVRMLNode::GetValue(const CVRMLFieldType* pvrft) const {
   return GetValue(pvrft->m_strName);
}

CVRMLFieldValue* CVRMLNode::GetFieldValue(const CString& strFieldName) const {
   return m_vrfvValues.GetNamed(strFieldName);
}

CVRMLFieldType* CVRMLNode::GetFieldType(const CString& strFieldName) const {
   return m_pvrntType->GetFieldTypeNamed(strFieldName);
}

CVRMLNodes::CVRMLNodes() {
   SetSize(0,1);
}

CVRMLNodes::~CVRMLNodes() {
   TRACE("Destroying CVRMLNodes\n");
   for (int i=0;i<GetSize();i++) {
      delete ElementAt(i);
      SetAt(i, NULL);
   }
   RemoveAll();
}

CVRMLNodeLib::CVRMLNodeLib() {
   m_bBuiltIn = FALSE;
}

CVRMLScene::CVRMLScene() {

}

CVRMLScene::~CVRMLScene() {
   TRACE("Destroying scene\n");
}

CVRMLScene::LoadScene(FILE* f) {
   BOOL bResult;

   yyrestart(f);
   bResult = !yyparse(this);
   return bResult;
}

CVRMLScene::LoadScene(CString strFileName) {
   BOOL bResult = FALSE;

   FILE* f;
   char *pAnsiString = new char[strFileName.GetLength()+1]; 
   wcstombs(pAnsiString, strFileName, strFileName.GetLength()+1); 

   f = fopen(pAnsiString,"ra");
   if (f) { 
      bResult = LoadScene(f);
      fclose(f);
   }
   
   return bResult;
}
