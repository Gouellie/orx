/**
 * @file orxContainerObject.h
 * @date [date]
 */

#ifndef _ORXCONTAINEROBJECT_H_
#define _ORXCONTAINEROBJECT_H_

#include "../Scroll/Scroll.h"
#include "orxContainerBank.h"

 /** Config defines
  */
#define orxCONTAINEROBJECT_KZ_CONFIG_MARGIN             "Margin"

typedef struct __orxCONTAINER_MARGIN_t
{
  orxS32 fLeft;
  orxS32 fTop;
  orxS32 fRight;
  orxS32 fBottom;
} orxCONTAINER_MARGIN
;

//! orxContainerObject class
class orxContainerObject : public ScrollObject
{

public:

                orxCONTAINER_MARGIN     GetMargin() const { return m_sMargin; };

protected:

                void                    OnCreate();
                void                    OnDelete();
                void                    Update(const orxCLOCK_INFO& _rstInfo);

private:

//! Variables
private:

                orxCONTAINER_MARGIN     m_sMargin = {};
};

#ifdef orxCONTAINER_IMPL

void orxContainerObject::OnCreate()
{
  if (orxConfig_HasValue(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN))
  {
    orxS32 sMarginCount;
    sMarginCount = orxConfig_GetListCount(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN);
    if (sMarginCount == 1)
    {
      /* Uniform Margin */
      orxS32 sMargin_Uniform = orxConfig_GetS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN);
      m_sMargin = { sMargin_Uniform, sMargin_Uniform, sMargin_Uniform, sMargin_Uniform };
    }
    else if (sMarginCount == 2)
    {
      /* Horizontal - Vertical Margin */
      orxS32 sMargin_Horizontal = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 0);
      orxS32 sMargin_Vertical   = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 1);
      m_sMargin = { sMargin_Horizontal, sMargin_Vertical, sMargin_Horizontal, sMargin_Vertical };
    }
    else if (sMarginCount == 4)
    {
      /* Custom Margin */
      orxS32 sMargin_Left   = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 0);
      orxS32 sMargin_Top    = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 1);
      orxS32 sMargin_Right  = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 2);
      orxS32 sMargin_Bottom = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 3);
      m_sMargin = { sMargin_Left, sMargin_Top, sMargin_Right, sMargin_Bottom };
    }
  }

  /* Register Object */
  orxContainerBank_RegisterContainer(GetOrxObject());
}

void orxContainerObject::OnDelete()
{

}

void orxContainerObject::Update(const orxCLOCK_INFO& _rstInfo)
{
}

#endif // orxCONTAINER_IMPL

#endif // _ORXCONTAINEROBJECT_H_
