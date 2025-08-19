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
#define orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION_HORIZONTAL   "horizontal"
#define orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION_VERTICAL     "vertical"
#define orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION_BOTH         "both"

#define orxCONTAINEROBJECT_KZ_CONFIG_ALIGNMENT                "Alignment"

typedef struct __orxCONTAINER_MARGIN_t
{
  orxFLOAT fLeft;
  orxFLOAT fTop;
  orxFLOAT fRight;
  orxFLOAT fBottom;
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
  orxCONTAINER_ORIENTATION_BOTH,

  orxCONTAINER_ORIENTATION_NONE = orxENUM_NONE    /**< Invalid status */

} orxCONTAINER_ORIENTATION;

//! orxContainerObject class
class orxContainerObject : public ScrollObject
{

public:

                virtual void                  GetMargin(orxVECTOR& vMargin)   const;
                virtual void                  GetOrigin(orxVECTOR& vOrigin)   const;
                virtual void                  GetSpacing(const orxVECTOR& vSize, orxVECTOR& vSpacing) const;

                virtual void                  SortChildren();
                virtual void                  SetChildOrigin(orxOBJECT* _pstChildObject, orxVECTOR& _vChildOrigin);
                virtual void                  FitChildInRect(orxOBJECT* _pstObject, const orxOBOX& p_rect);

protected:

                void                          OnCreate();
                void                          OnDelete();
                void                          Update(const orxCLOCK_INFO& _rstInfo);

private:

                orxCONTAINER_TYPE             m_eContainerType;
                orxCONTAINER_ORIENTATION      m_eContainerOrientation;

                orxS32                        m_s32Spacing                = orxS32(0);
                orxCONTAINER_MARGIN           m_stMargin                  = {};

                orxU32                        m_u32AlingFlags             = orxGRAPHIC_KU32_FLAG_ALIGN_CENTER;

                orxBOOL                       m_bNeedUpdate               = orxTRUE;
                orxVECTOR                     m_vPreviousSize;
                orxFLOAT                      m_fRotation;

private:

};

#ifdef orxCONTAINER_IMPL

void orxContainerObject::OnCreate()
{
  // cache size
  GetSize(m_vPreviousSize);
  m_fRotation = GetRotation();

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
    if (orxString_Compare(zContainerOrientation, orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION_HORIZONTAL) == 0)
    {
      m_eContainerOrientation = orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_HORIZONTAL;
    }
    else if (orxString_Compare(zContainerOrientation, orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION_VERTICAL) == 0)
    {
      m_eContainerOrientation = orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_VERTICAL;
    }
    else if (orxString_Compare(zContainerOrientation, orxCONTAINEROBJECT_KZ_CONFIG_ORIENTATION_BOTH) == 0)
    {
      m_eContainerOrientation = orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_BOTH;
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
      orxFLOAT fMargin_Uniform = orxConfig_GetListFloat(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 0);
      m_stMargin = { fMargin_Uniform, fMargin_Uniform, fMargin_Uniform, fMargin_Uniform };
    }
    else if (sMarginCount == 2)
    {
      /* Horizontal - Vertical Margin */
      orxFLOAT fMargin_Horizontal = orxConfig_GetListFloat(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 0);
      orxFLOAT fMargin_Vertical   = orxConfig_GetListFloat(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 1);
      m_stMargin = { fMargin_Horizontal, fMargin_Vertical, fMargin_Horizontal, fMargin_Vertical };
    }
    else if (sMarginCount == 4)
    {
      /* Custom Margin */
      orxFLOAT fMargin_Left   = orxConfig_GetListFloat(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 0);
      orxFLOAT fMargin_Top    = orxConfig_GetListFloat(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 1);
      orxFLOAT fMargin_Right  = orxConfig_GetListFloat(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 2);
      orxFLOAT fMargin_Bottom = orxConfig_GetListFloat(orxCONTAINEROBJECT_KZ_CONFIG_MARGIN, 3);
      m_stMargin = { fMargin_Left, fMargin_Top, fMargin_Right, fMargin_Bottom };
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
  orxFLOAT fCurrentRotation = GetRotation();
  if (fCurrentRotation != m_fRotation)
  {
    m_fRotation = fCurrentRotation;
    m_bNeedUpdate = orxTRUE;
  }

  orxVECTOR vCurrentSize;
  GetSize(vCurrentSize);
  if (orxVector_GetDistance(&vCurrentSize, &m_vPreviousSize))
  {
    orxVector_Copy(&m_vPreviousSize, &vCurrentSize);
    m_bNeedUpdate = orxTRUE;
  }
}

void orxContainerObject::GetOrigin(orxVECTOR& vOrigin) const
{
  orxOBOX stBoundingBox;
  orxObject_GetBoundingBox(GetOrxObject(), &stBoundingBox);

  orxVECTOR vTopLeft;
  orxVector_Sub(&vTopLeft, &(stBoundingBox.vPosition), &(stBoundingBox.vPivot));

  orxVector_Copy(&vOrigin, &vTopLeft);

  /* Align right? */
  if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_RIGHT))
  {
    orxVector_Add(&vOrigin, &vOrigin, &(stBoundingBox.vX));
  }
  else if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_LEFT))
  {
    // nothing
  }
  /* Align center */
  else
  {
    orxVECTOR vHalfX;
    orxVector_Mulf(&vHalfX, &(stBoundingBox.vX),0.5f);
    orxVector_Add(&vOrigin, &vOrigin, &vHalfX);
  }

  /* Align bottom? */
  if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_BOTTOM))
  {
    orxVector_Add(&vOrigin, &vOrigin, &(stBoundingBox.vY));
  }
  else if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_TOP))
  {
    // nothing
  }
  /* Align center */
  else
  {
    orxVECTOR vHalfY;
    orxVector_Mulf(&vHalfY, &(stBoundingBox.vY), 0.5f);
    orxVector_Add(&vOrigin, &vOrigin, &vHalfY);
  }
}

void orxContainerObject::SortChildren()
{
  // TODO need to change sort children logic.
  // First loop offsets the children positions starting from zero and calculates the rect dimension (space occupied by children + spacing)
  // Second loop offsets the children positions based on the rect dimension and alignment (anchor is calculated at the end)

  if (m_bNeedUpdate)
  {
    orxVECTOR vOrigin;
    GetOrigin(vOrigin);

    orxVECTOR vAnchor, vRectDimension;
    orxVector_Copy(&vAnchor, &vOrigin);

    vRectDimension = orxVECTOR_0;

    orxVECTOR vMargin;
    GetMargin(vMargin);
    orxVector_Add(&vAnchor, &vAnchor, &vMargin);

    orxVECTOR vSpacing, vSize;
    vSpacing = orxVECTOR_0;
    for (orxOBJECT* pstChild = orxObject_GetOwnedChild(GetOrxObject());
      pstChild != orxNULL;
      pstChild = orxObject_GetOwnedSibling(pstChild))
    {
      orxVector_Add(&vAnchor, &vAnchor, &vSpacing);
      SetChildOrigin(pstChild, vAnchor);
      orxObject_GetSize(pstChild, &vSize);
      GetSpacing(vSize, vSpacing);
      vRectDimension.fX = vSize.fX;
    }

    orxBOOL hasRightLeftAlignment = orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_RIGHT | orxGRAPHIC_KU32_FLAG_ALIGN_LEFT);
    orxBOOL hasTopBottomAlignment = orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_TOP | orxGRAPHIC_KU32_FLAG_ALIGN_BOTTOM);

    if (hasRightLeftAlignment && hasTopBottomAlignment)
    {
      return;
    }

    vRectDimension.fY = vAnchor.fY;

    orxVECTOR vHalf;
    orxVector_Mulf(&vHalf, &vRectDimension, orxFLOAT(0.5f));

    if (hasRightLeftAlignment)
    {
      vHalf.fX = orxFLOAT_0;
    }
    if (hasTopBottomAlignment)
    {
      vHalf.fY = orxFLOAT_0;
    }

    orxVECTOR vPos;
    for (orxOBJECT* pstChild = orxObject_GetOwnedChild(GetOrxObject());
      pstChild != orxNULL;
      pstChild = orxObject_GetOwnedSibling(pstChild))
    {
      orxObject_GetPosition(pstChild, &vPos);
      orxVector_Sub(&vPos, &vPos, &vHalf);
      orxObject_SetPosition(pstChild, &vPos);
    }

    m_bNeedUpdate = orxFALSE;
  }
}

void orxContainerObject::SetChildOrigin(orxOBJECT* _pstChildObject, orxVECTOR& _vChildOrigin)
{
  orxOBOX stBoundingBox;
  orxObject_GetBoundingBox(_pstChildObject, &stBoundingBox);

  orxVECTOR vPosition, vObjectOrigin, vOffset, vCenter;
  orxObject_GetPosition(_pstChildObject, &vPosition);
  orxOBox_GetCenter(&stBoundingBox, &vCenter);

  orxFLOAT fZ = vPosition.fZ;


  /* Gets current origin TOP LEFT */
  orxVector_Sub(&vObjectOrigin, &(stBoundingBox.vPosition), &(stBoundingBox.vPivot));

  /* Is Right Aligned */
  if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_RIGHT))
  {
    orxVector_Add(&vObjectOrigin, &vObjectOrigin, &(stBoundingBox.vX));
  }
  else if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_LEFT))
  {
    /* do nothing */
  }
  else
  {

  }

  /* Is Bottom Aligned */
  if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_BOTTOM))
  {
    orxVector_Add(&vObjectOrigin, &vObjectOrigin, &(stBoundingBox.vY));
  }

  /* Gets offset to destination */
  orxVector_Sub(&vOffset, &_vChildOrigin, &vObjectOrigin);

  /* Clear Z */
  vOffset.fZ = orxFLOAT_0;

  /* Update Position with Offset */
  orxVector_Add(&vPosition, &vOffset, &vPosition);

  /* Update Position */
  orxObject_SetPosition(_pstChildObject, &vPosition);
}

void orxContainerObject::FitChildInRect(orxOBJECT* _pstObject, const orxOBOX& p_rect)
{

}

void orxContainerObject::GetMargin(orxVECTOR& vMargin) const
{
  /* Init */
  vMargin = orxVECTOR_0;

  /* Align left? */
  if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_LEFT))
  {
    vMargin.fX = m_stMargin.fLeft;
  }
  /* Align right? */
  else if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_RIGHT))
  {
    vMargin.fX = -m_stMargin.fRight;
  }

  /* Align top? */
  if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_TOP))
  {
    vMargin.fY = m_stMargin.fTop;
  }
  /* Align bottom? */
  else if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_BOTTOM))
  {
    vMargin.fY = -m_stMargin.fBottom;
  }

  orxFLOAT fRotation = GetRotation();
  if (fRotation) {
    orxVector_2DRotate(&vMargin, &vMargin, GetRotation());
  }
}

void orxContainerObject::GetSpacing(const orxVECTOR& vSize, orxVECTOR& vSpacing) const
{
  /* Init */
  vSpacing = orxVECTOR_0;
  if (m_eContainerOrientation == orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_VERTICAL)
  {
    /* Align top? */
    if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_BOTTOM))
    {
      /* bottom going up */
      vSpacing.fX = orxFLOAT_0;
      vSpacing.fY = -(vSize.fY + m_s32Spacing);
      vSpacing.fZ = orxFLOAT_0;
    }
    else
    {
      /* top going down */
      vSpacing.fX = orxFLOAT_0;
      vSpacing.fY = vSize.fY + m_s32Spacing;
      vSpacing.fZ = orxFLOAT_0;
    }
  }
  else if (m_eContainerOrientation == orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_HORIZONTAL)
  {
    /* Align left? */
    if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_RIGHT))
    {
      /* right going left */
      vSpacing.fX = -(vSize.fX + m_s32Spacing);
      vSpacing.fY = orxFLOAT_0;
      vSpacing.fZ = orxFLOAT_0;
    }
    else
    {
      /* left going right */
      vSpacing.fX = vSize.fX + m_s32Spacing;
      vSpacing.fY = orxFLOAT_0;
      vSpacing.fZ = orxFLOAT_0;
    }
  }
  else if (m_eContainerOrientation == orxCONTAINER_ORIENTATION::orxCONTAINER_ORIENTATION_BOTH)
  {
    /* Align left? */
    if (orxFLAG_TEST(m_u32AlingFlags, orxGRAPHIC_KU32_FLAG_ALIGN_RIGHT))
    {
      /* right going left */
      vSpacing.fX = -(vSize.fX + m_s32Spacing);
      vSpacing.fY = -(vSize.fY + m_s32Spacing);
      vSpacing.fZ = orxFLOAT_0;
    }
    else
    {
      /* left going right */
      vSpacing.fX = vSize.fX + m_s32Spacing;
      vSpacing.fY = vSize.fY + m_s32Spacing;
      vSpacing.fZ = orxFLOAT_0;
    }
  }

  orxFLOAT fRotation = GetRotation();
  if (fRotation) {
    orxVector_2DRotate(&vSpacing, &vSpacing, GetRotation());
  }
}

#endif // orxCONTAINER_IMPL

#endif // _ORXCONTAINEROBJECT_H_
