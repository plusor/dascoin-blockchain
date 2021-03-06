/*
 * DASCOIN!
 */
#pragma once

#include <graphene/chain/protocol/types.hpp>
#include <graphene/db/object.hpp>
#include <graphene/db/generic_index.hpp>

#include <boost/multi_index/composite_key.hpp>

namespace graphene {
namespace chain {

class frequency_history_record_object : public graphene::db::abstract_object<frequency_history_record_object> {
  public:
    static const uint8_t space_id = implementation_ids;
    static const uint8_t type_id = impl_frequency_history_record_object_type;

    account_id_type authority;
    frequency_type frequency;
    time_point_sec time;
    string comment;

    frequency_history_record_object() = default;
    explicit frequency_history_record_object(account_id_type authority, frequency_type frequency, 
                                             time_point_sec time, const string& comment) 
      : authority(authority),
        frequency(frequency),
        time(time),
        comment(comment) {}
};

struct by_time;
struct by_frequency;

typedef multi_index_container<
  frequency_history_record_object,
    indexed_by<
      ordered_unique<
        tag<by_id>, 
        member<object, object_id_type, &object::id>
      >,
      ordered_unique<tag<by_time>,
        composite_key<frequency_history_record_object,
          member<frequency_history_record_object, time_point_sec, &frequency_history_record_object::time>,
          member<object, object_id_type, &object::id>
        >
      >,
      ordered_unique<tag<by_frequency>,
        composite_key<frequency_history_record_object,
          member<frequency_history_record_object, frequency_type, &frequency_history_record_object::frequency>,
          member<object, object_id_type, &object::id>
        >
      >
    >
> frequency_history_record_object_multi_index_type;

typedef generic_index<frequency_history_record_object, frequency_history_record_object_multi_index_type> frequency_history_record_index;

}  // namespace chain
}  // namespace graphene

FC_REFLECT_DERIVED( graphene::chain::frequency_history_record_object, (graphene::db::object),
                    (authority)
                    (frequency)
                    (time)
                    (comment)
                  )