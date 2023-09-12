/*****************************************************************************
 *
 * File			: NtlPLResouce.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 21	
 * Abstract		: Presentation layer resource base class
 *****************************************************************************
 * Desc         : 
 * Adjust		: HuunSuk, Jang(2005. 7 29)
 *				    - dictory type ����/�Լ� �߰�.
 *
 *****************************************************************************/

#ifndef __NTL_PLRESOURCE_H__
#define __NTL_PLRESOURCE_H__

#include <list>
#include <rwcore.h>
#include <rpworld.h>
#include <rtanim.h> 

/**
 * \ingroup NtlPresentation
 * RenderWare resource wrapping class�̴�.
 * RenderWare������ clump �� atomic data�� clone�� �� �� �ִµ�, 
 * resource�� �ϰ��� �ִ� ������ ���Ͽ� ���� �̸��� data�� ����� ��� reference count�� ����Ͽ�����, 
 * clone resource�� ��쿡�� original CNtlPLResource�� clone list�� CNtlPLReseource�� link �ϴ� ����� �����Ͽ���.
 */

class CNtlPLResource
{
private:

	std::string m_strName;					/**< String describing the resource name */
	unsigned int m_uiType;					/**< id describing the resource type */
	const void *m_pData;					/**< Pointer to resource */
    unsigned int m_uiRefCount;				/**< Reference count used to lock the resource */
	bool m_bClone;

public:
      
	  CNtlPLResource(void) { m_uiType = 0; m_uiRefCount = 0; m_pData = NULL; m_bClone = false; }
	  ~CNtlPLResource(void) {} 
	  
      /**
      *  Set the name of the resource, managed by this CResource object.
      *
      *  \param pName A string containing the name of the resource.
      */
	  void SetName(const char *pName) { m_strName = pName; }

      /**
      *  Set the type of the resource, managed by this CResource object.
      *
      *   \param pType A unsigned int containing the type of the resource.
      */
      void SetType(unsigned int uiType)  {  m_uiType = uiType; }
     
	  /**
      *  Set resource pointer to the resource, managed by this CResource object.
      *
      *   \param bClone renderware resource clone flag
      */
	  void SetClone(bool bClone) { m_bClone = bClone; }

      /**
      *  Set resource pointer to the resource, managed by this CResource object.
      *
      *   \param pResource A pointer to the resource
      */
      void SetData(const void *pData) { m_pData = pData; }
          
      /**
      *  refcount of the resource, increment.
      */
      void AddRef(void) { m_uiRefCount++; }

	  /**
      *  refcount of the resource, decrement.
      */
	  void ReleaseRef(void) { if(m_uiRefCount > 0) m_uiRefCount--; }
      
      /**
      *  Get the name of the resource, managed by this CResource object.
      *
      *   \return A string containing the type of the resource.
      */
      const char* GetName(void) const {return m_strName.c_str(); }

      /**
      *  Get the type of the resource, managed by this CResource object.
      *
      *   \return A unsigned int containing the type of the resource.
      */
      unsigned int GetType(void) const {return m_uiType;}

       /**
      *  Get the type of the resource, managed by this CResource object.
      *
      *   \return clone flag the renderware resource.
      */

	  bool GetClone(void) const { return m_bClone; }

      /**
      *  Get resource pointer to the resource, managed by this CResource object.
      *
      *   \return A pointer to the resource
      */
      const void* GetData(void) const {return m_pData;}
      
      /**
      *  Get the lock refcount of the resource, managed by this CResource object.
      *
      *   \return The lock refcount of this resource
      */
      unsigned int GetRefCount(void) const {return m_uiRefCount;}

	  /**
      *  RpWorld pointer�� casting �Ѵ�.
      */
	  RpWorld* GetWorld(void) { return reinterpret_cast<RpWorld*>(const_cast<void*>(m_pData)); }

  	  /**
      *  RpClump pointer�� casting �Ѵ�.
      */
	  RpClump* GetClump(void) { return reinterpret_cast<RpClump*>(const_cast<void*>(m_pData)); }

	  /**
      *  RpAtomic pointer�� casting �Ѵ�.
      */
	  RpAtomic* GetAtomic(void) { return reinterpret_cast<RpAtomic*>(const_cast<void*>(m_pData)); }

	  /**
      *  RtAnimAnimation pointer�� casting �Ѵ�.
      */
	  RtAnimAnimation* GetAnimation(void) { return reinterpret_cast<RtAnimAnimation*>(const_cast<void*>(m_pData)); }
};


#endif
