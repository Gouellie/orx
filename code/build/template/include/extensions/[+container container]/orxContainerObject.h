//! Includes

#ifndef _ORXCONTAINEROBJECT_H_
#define _ORXCONTAINEROBJECT_H_

#include "../Scroll/Scroll.h"
#include "orxContainerBank.h"

 /** Config defines
  */
#define orxCONTAINEROBJECT_KZ_CONFIG_MARGIN                   "Margin"
#define orxCONTAINEROBJECT_KZ_CONFIG_SPACING                  "Spacing"

#define orxCONTAINEROBJECT_KZ_CONFIG_CONTAINER_TYPE           "ContainerType"
#define orxCONTAINEROBJECT_KZ_CONFIG_STACK_PANEL              "StackPanel"
#define orxCONTAINEROBJECT_KZ_CONFIG_STACK_GRID               "Grid"

#define orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION              "Orientation"
#define orxCONTAINEROBJECT_KZ_CONFIG_HORIZONTAL               "Horizontal"
#define orxCONTAINEROBJECT_KZ_CONFIG_VERTICAL                 "Vertical"

#define orxCONTAINEROBJECT_KZ_CONFIG_ALIGNMENT                "Alignment"

typedef struct __orxCONTAINER_MARGIN_t
{
  orxS32 fLeft;
  orxS32 fTop;
  orxS32 fRight;
  orxS32 fBottom;
} orxCONTAINER_MARGIN;

typedef enum __orxCONTAINER_TYPE_t
{
  orxCONTAINER_TYPE_STACK_PANEL = 0,
  orxCONTAINER_TYPE_GRID,

  orxCONTAINER_TYPE_NONE = orxENUM_NONE           /**< Invalid status */

} orxCONTAINER_TYPE;

typedef enum __orxCONTAINER_ORIENTATION_t
{
  orxCONTAINER_ORIENTATION_VERTICAL = 0,
  orxCONTAINER_ORIENTATION_HORIZONTAL,

  orxCONTAINER_ORIENTATION_NONE = orxENUM_NONE    /**< Invalid status */

} orxCONTAINER_ORIENTATION;

//! orxContainerObject class
class orxContainerObject : public ScrollObject
{

public:

                orxS32                        GetSpacing()                const { return m_s32Spacing; }
                orxCONTAINER_MARGIN           GetMargin()                 const { return m_stMargin; }
                orxCONTAINER_TYPE             GetContainerType()          const { return m_eContainerType; }
                orxCONTAINER_ORIENTATION      GetContainerOrientation()   const { return m_eContainerOrientation; }
                orxU32                        GetAlingFlags()             const { return m_u32AlingFlags; }

                virtual const orxVECTOR&      GetOrigin() const;

protected:

                void                          OnCreate();
                void                          OnDelete();
                void                          Update(const orxCLOCK_INFO& _rstInfo);

private:

//! Variables
private:

                orxS32                        m_s32Spacing                = orxS32(0);
                orxCONTAINER_MARGIN           m_stMargin                  = {};
                orxCONTAINER_TYPE             m_eContainerType;
                orxCONTAINER_ORIENTATION      m_eContainerOrientation;
                orxU32                        m_u32AlingFlags             = orxGRAPHIC_KU32_FLAG_ALIGN_TOP | orxGRAPHIC_KU32_FLAG_ALIGN_LEFT;
};

#ifdef orxCONTAINER_IMPL

void orxContainerObject::OnCreate()
{
  /* Default initialization */
  m_eContainerType        = orxCONTAINER_TYPE::orxCONTAINER_TYPE_STACK_PANEL;
  m_eContainerOrientation = orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_VERTICAL;

  /* Set Container Type */
  if (orxConfig_HasValue(orxCONTAINEROBJECT_KZ_CONFIG_CONTAINER_TYPE))
  {
    const orxSTRING zContainerType = orxConfig_GetString(orxCONTAINEROBJECT_KZ_CONFIG_CONTAINER_TYPE);
    if (orxString_Compare(zContainerType, orxCONTAINEROBJECT_KZ_CONFIG_STACK_PANEL) == 0)
    {
      m_eContainerType = orxCONTAINER_TYPE::orxCONTAINER_TYPE_STACK_PANEL;
    }
    else if (orxString_Compare(zContainerType, orxCONTAINEROBJECT_KZ_CONFIG_STACK_GRID) == 0)
    {
      m_eContainerType = orxCONTAINER_TYPE::orxCONTAINER_TYPE_GRID;
    }
  }

  /* Set Container Orientation */
  if (orxConfig_HasValue(orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION))
  {
    const orxSTRING zContainerOrientation = orxConfig_GetString(orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION);
    if (orxString_Compare(zContainerOrientation, orxCONTAINEROBJECT_KZ_CONFIG_HORIZONTAL) == 0)
    {
      m_eContainerOrientation = orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_HORIZONTAL;
    }
    else if (orxString_Compare(zContainerOrientation, orxCONTAINEROBJECT_KZ_CONFIG_VERTICAL) == 0)
    {
      m_eContainerOrientation = orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_VERTICAL;
    }
  }

  /* Set Spacing */
  if (orxConfig_HasValue(orxCONTAINEROBJECT_KZ_CONFIG_SPACING))
  {
    m_s32Spacing = orxConfig_GetS32(orxCONTAINEROBJECT_KZ_CONFIG_SPACING);
  }

  /* Set Margin */
  if (orxConfig_HasValue(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN))
  {
    orxS32 sMarginCount;
    sMarginCount = orxConfig_GetListCount(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN);
    if (sMarginCount == 1)
    {
      /* Uniform Margin */
      orxS32 sMargin_Uniform = orxConfig_GetS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN);
      m_stMargin = { sMargin_Uniform, sMargin_Uniform, sMargin_Uniform, sMargin_Uniform };
    }
    else if (sMarginCount == 2)
    {
      /* Horizontal - Vertical Margin */
      orxS32 sMargin_Horizontal = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 0);
      orxS32 sMargin_Vertical   = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 1);
      m_stMargin = { sMargin_Horizontal, sMargin_Vertical, sMargin_Horizontal, sMargin_Vertical };
    }
    else if (sMarginCount == 4)
    {
      /* Custom Margin */
      orxS32 sMargin_Left   = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 0);
      orxS32 sMargin_Top    = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 1);
      orxS32 sMargin_Right  = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 2);
      orxS32 sMargin_Bottom = orxConfig_GetListS32(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 3);
      m_stMargin = { sMargin_Left, sMargin_Top, sMargin_Right, sMargin_Bottom };
    }
  }

  if (orxConfig_HasValue(orxCONTAINEROBJECT_KZ_CONFIG_ALIGNMENT))
  {
    m_u32AlingFlags = orxGraphic_GetAlignFlags(orxConfig_GetString(orxCONTAINEROBJECT_KZ_CONFIG_ALIGNMENT));
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

inline const orxVECTOR& orxContainerObject::GetOrigin() const
{
  orxOBOX stBoundingBox;
  orxObject_GetBoundingBox(GetOrxObject(), &stBoundingBox);

  orxVECTOR vOrigin;
  /* Gets origin */
  orxVector_Sub(&vOrigin, &(stBoundingBox.vPosition), &(stBoundingBox.vPivot));

  /* Align left? */
  if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_LEFT))
  {
  }
  /* Align right? */
  else if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_RIGHT))
  {
  }
  /* Align center */
  else
  {

  }

  /* Align top? */
  if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_TOP))
  {

  }
  /* Align bottom? */
  else if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_BOTTOM))
  {
  }
  /* Align center */
  else
  {
  }

  return vOrigin;
}

#endif // orxCONTAINER_IMPL

#endif // _ORXCONTAINEROBJECT_H_
