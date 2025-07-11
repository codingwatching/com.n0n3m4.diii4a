/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#ifndef _EntitiesMP_BlendController_INCLUDED
#define _EntitiesMP_BlendController_INCLUDED 1
#include <EntitiesMP/Marker.h>
extern DECL_DLL CEntityPropertyEnumType BlendControllerType_enum;
enum BlendControllerType {
  BCT_NONE = 0,
  BCT_PYRAMID_PLATES = 1,
  BCT_ACTIVATE_PLATE_1 = 2,
  BCT_ACTIVATE_PLATE_2 = 3,
  BCT_ACTIVATE_PLATE_3 = 4,
  BCT_ACTIVATE_PLATE_4 = 5,
  BCT_ACTIVATE_PYRAMID_MORPH_ROOM = 6,
};
DECL_DLL inline void ClearToDefault(BlendControllerType &e) { e = (BlendControllerType)0; } ;
extern "C" DECL_DLL CDLLEntityClass CBlendController_DLLClass;
class CBlendController : public CMarker {
public:
virtual BOOL IsImportant(void) const { return TRUE; };
  DECL_DLL virtual void SetDefaultProperties(void);
  enum BlendControllerType m_bctType;
   
#line 54 "/data/data/com.termux/files/home/doom3/SeriousSamClassic-1.10.7/SamTSE/Sources/EntitiesMP/BlendController.es"
BOOL HandleEvent(const CEntityEvent & ee);
#define  STATE_CBlendController_Main 1
  BOOL 
#line 114 "/data/data/com.termux/files/home/doom3/SeriousSamClassic-1.10.7/SamTSE/Sources/EntitiesMP/BlendController.es"
Main(const CEntityEvent &__eeInput);
};
#endif // _EntitiesMP_BlendController_INCLUDED
