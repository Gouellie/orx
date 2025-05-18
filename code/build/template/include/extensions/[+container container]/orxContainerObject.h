/**
 * @file orxContainerObject.h
 * @date [date]
 */

#ifndef _ORXCONTAINEROBJECT_H_
#define _ORXCONTAINEROBJECT_H_

#include "[name].h"

//! orxContainerObject class
class orxContainerObject : public ScrollObject
{

public:

protected:

                void                    OnCreate();
                void                    OnDelete();
                void                    Update(const orxCLOCK_INFO& _rstInfo);

private:

//! Variables
private:

};

#ifdef orxCONTAINER_IMPL

void orxContainerObject::OnCreate()
{

}

void orxContainerObject::OnDelete()
{

}

void orxContainerObject::Update(const orxCLOCK_INFO& _rstInfo)
{
}

#endif // orxCONTAINER_IMPL

#endif // _ORXCONTAINEROBJECT_H_
