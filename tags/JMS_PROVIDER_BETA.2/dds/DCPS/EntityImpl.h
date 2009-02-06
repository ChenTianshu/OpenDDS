// -*- C++ -*-
//
// $Id$
#ifndef TAO_DDS_DCPS_ENTITY_IMPL_H
#define TAO_DDS_DCPS_ENTITY_IMPL_H

#include "dds/DdsDcpsInfrastructureS.h"
#include "ace/Atomic_Op_T.h"
#include "dds/DCPS/LocalObject.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

namespace OpenDDS
{
  namespace DCPS
  {
    /**
    * @class EntityImpl
    *
    * @brief Implements the ::OpenDDS::DCPS::Entity
    *        interfaces.
    *
    * This class is the base class of other servant classes.
    * e.g. DomainParticipantImpl, PublisherImpl ...
    */
    class OpenDDS_Dcps_Export EntityImpl
      : public virtual LocalObject<DDS::Entity>
    {
    public:
      ///Constructor
      EntityImpl ();

      ///Destructor
      virtual ~EntityImpl ();

      virtual ::DDS::ReturnCode_t set_enabled (
        )
        ACE_THROW_SPEC ((
          CORBA::SystemException
        ));

      virtual ::DDS::StatusCondition_ptr get_statuscondition (
        )
        ACE_THROW_SPEC ((
          CORBA::SystemException
        ));

      virtual ::DDS::StatusKindMask get_status_changes (
        )
        ACE_THROW_SPEC ((
          CORBA::SystemException
        ));

      virtual void set_deleted (bool state);

      virtual bool get_deleted ();

      void set_status_changed_flag (::DDS::StatusKind status,
                                    bool status_changed_flag);

      /// Call this *after* dispatching to listeners when the "changed status
      /// flag" is enabled so that any waiting waitsets can be unblocked.
      void notify_status_condition ();

    protected:
      /// The flag indicates the entity is enabled.
      ACE_Atomic_Op<TAO_SYNCH_MUTEX, bool>       enabled_;

      /// The flag indicates the entity is being deleted.
      ACE_Atomic_Op<TAO_SYNCH_MUTEX, bool>       entity_deleted_;

    private:
      /// The status_changes_ variable lists all status changed flag.
      /// The StatusChangedFlag becomes TRUE whenever the plain communication
      /// status changes and it is reset to FALSE each time the application
      /// accesses the plain communication status via the proper
      /// get_<plain communication status> operation on the Entity.
      DDS::StatusKindMask status_changes_;
      DDS::StatusCondition_var status_condition_;

      ACE_Thread_Mutex    lock_;  
    };

  } // namespace DCPS
} // namespace OpenDDS

#endif /* TAO_DDS_DCPS_ENTITY_IMPL_H */
