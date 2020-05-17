#pragma once

#include <eosio/chain/authority.hpp>
#include <eosio/chain/chain_config.hpp>
#include <eosio/chain/config.hpp>
#include <eosio/chain/types.hpp>

namespace eosio { namespace chain {

using action_name    = eosio::chain::action_name;

struct newaccount {
   account_name                     creator;
   account_name                     name;
   authority                        owner;
   authority                        active;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(newaccount);
   }
};

// by myextend
struct bindattrs {
   account_name                     account;
   uint32_t                         attrs = 0;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(bindattrs);
   }
};

struct bindapp {
   account_name                     account;
   uint32_t                         opr_code;
   uint32_t                         opr;
   uint32_t                         appid;
   time_point                       expire;
   string                           memo;

   enum class opr_code {
      modify = 1,
      transfer = 2,
      create = 3
   };

   enum class opr_fields : uint32_t {
      expire = 1,
      memo = 2
   };

   bool has_expire() {
      return has_field( opr, opr_fields::expire );
   }

   void set_expire( bool expire ) {
      opr = set_field( opr, opr_fields::expire, expire );
   }

   bool has_memo() {
      return has_field( opr, opr_fields::memo );
   }

   void set_memo( bool memo ) {
      opr = set_field( opr, opr_fields::memo, memo );
   }

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(bindapp);
   }
};

struct bindsym {
   account_name                     account;
   uint32_t                         opr_code;
   uint32_t                         opr;
   uint64_t                         sym;
   account_name                     tollor;
   account_name                     issuer;
   uint64_t                         minval   = 0;
   uint64_t                         minfee   = 0;
   uint64_t                         level    = 0;
   uint64_t                         delta    = 0;
   uint64_t                         maxfee   = 0;

   enum class opr_code {
      modify = 1,
      transfer = 2,
      create = 3
   };

   enum class opr_fields : uint32_t {
      tollor = 1,
      issuer = 2,
      fee = 4
   };

   bool has_tollor() {
      return has_field( opr, opr_fields::tollor );
   }

   void set_tollor( bool tollor ) {
      opr = set_field( opr, opr_fields::tollor, tollor );
   }

   bool has_issuer() {
      return has_field(opr, opr_fields::issuer);
   }

   void set_issuer( bool issuer ) {
      opr = set_field( opr, opr_fields::issuer, issuer );
   }

   bool has_fee() {
      return has_field(opr, opr_fields::fee);
   }

   void set_fee( bool fee ) {
      opr = set_field( opr, opr_fields::fee, fee );
   }

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(bindsym);
   }
};

struct bindmsg {
   account_name                     account;
   account_name                     to;
   string                           msg;
   string                           sign;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(bindmsg);
   }
};
//

struct setcode {
   account_name                     account;
   uint8_t                          vmtype = 0;
   uint8_t                          vmversion = 0;
   bytes                            code;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(setcode);
   }
};

struct setabi {
   account_name                     account;
   bytes                            abi;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(setabi);
   }
};


struct updateauth {
   account_name                      account;
   permission_name                   permission;
   permission_name                   parent;
   authority                         auth;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(updateauth);
   }
};

struct deleteauth {
   deleteauth() = default;
   deleteauth(const account_name& account, const permission_name& permission)
   :account(account), permission(permission)
   {}

   account_name                      account;
   permission_name                   permission;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(deleteauth);
   }
};

struct linkauth {
   linkauth() = default;
   linkauth(const account_name& account, const account_name& code, const action_name& type, const permission_name& requirement)
   :account(account), code(code), type(type), requirement(requirement)
   {}

   account_name                      account;
   account_name                      code;
   action_name                       type;
   permission_name                   requirement;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(linkauth);
   }
};

struct unlinkauth {
   unlinkauth() = default;
   unlinkauth(const account_name& account, const account_name& code, const action_name& type)
   :account(account), code(code), type(type)
   {}

   account_name                      account;
   account_name                      code;
   action_name                       type;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(unlinkauth);
   }
};

struct canceldelay {
   permission_level      canceling_auth;
   transaction_id_type   trx_id;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(canceldelay);
   }
};

struct onerror {
   uint128_t      sender_id;
   bytes          sent_trx;

   onerror( uint128_t sid, const char* data, size_t len )
   :sender_id(sid),sent_trx(data,data+len){}

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(onerror);
   }
};

} } /// namespace eosio::chain

FC_REFLECT( eosio::chain::newaccount                       , (creator)(name)(owner)(active) )
FC_REFLECT( eosio::chain::setcode                          , (account)(vmtype)(vmversion)(code) )
FC_REFLECT( eosio::chain::setabi                           , (account)(abi) )
FC_REFLECT( eosio::chain::updateauth                       , (account)(permission)(parent)(auth) )
FC_REFLECT( eosio::chain::deleteauth                       , (account)(permission) )
FC_REFLECT( eosio::chain::linkauth                         , (account)(code)(type)(requirement) )
FC_REFLECT( eosio::chain::unlinkauth                       , (account)(code)(type) )
FC_REFLECT( eosio::chain::canceldelay                      , (canceling_auth)(trx_id) )
FC_REFLECT( eosio::chain::onerror                          , (sender_id)(sent_trx) )
// by myextend
FC_REFLECT( eosio::chain::bindattrs                        , (account)(attrs) )
FC_REFLECT( eosio::chain::bindapp                          , (account)(opr_code)(opr)(appid)(expire)(memo) )
FC_REFLECT( eosio::chain::bindsym                          , (account)(opr_code)(opr)(sym)(tollor)(issuer)(minval)(minfee)(level)(delta)(maxfee) )
FC_REFLECT( eosio::chain::bindmsg                          , (account)(to)(msg)(sign) )
//
