<h1>UAC</h1>
Universal Application Chain extended from EOS chain.

<h1>Purpose</h1>

To realize a dedicated public chain under control, supporting cross-chain, fast transfer, asset tokenization, custody, settlement and other services.
The EOS public chain code is selected as the basis for expansion, mainly because the EOS public chain has the following characteristics,
1. The account authorization mechanism is relatively complete.
2. The packing speed is relatively fast.
3. The energy consumption of the public chain is relatively low.
With simple extensions, business needs can be supported.

Main extended functions:
1. By default, it is forbidden for the account to set a contract and restrict the permission to publish applications.
2. Increase the role of application administrator and jointly manage resources such as applications and tokens.
3. Increase application attributes and restrict the use of applications.
4. Add token attributes to restrict the use of tokens.


<h1>Build</h1>

<pre>
git clone https://github.com/EOSIO/eos --recursive
git checkout -b v2.0.5
</pre>

<pre>
git clone --recursive https://github.com/eosio/eosio.cdt
git checkout -b v1.7.0-rc1
</pre>

<pre>
git clone --recursive https://github.com/EOSIO/eosio.contracts.git
git checkout -b v1.9.1
</pre>

<pre>
git clone https://github.com/myshare2020/uac --recursive
Use the uac files to overwrite the files in the corresponding directories.
</pre>

<h1>Extentions</h1>

<h2>Expand built-in account</h2>

eosio.app
<p>application administrator account</p>

<h2>Extended interface commands</h2>

1. Set account properties
<p>Application administrator authorization is required.</p>
<pre>
bindattrs &lt;account&gt;
account user account
--can_set_contract Allow account to set contract
</pre>

2. Set application properties
<p>The operation account, application account, and application administrator authorization are required.</p>
<pre>
bindapp &lt;account&gt; &lt;opr_code&gt; &lt;appid&gt;
account Operation account
opr_code operation
  modify modify application attributes
  transfer transfer application ownership
  create create application
appid application id

--has_memo modify memo
--memo application description (800 bytes)
--has_expire modify expire
--expire Application expiration time (ISO time format)
</pre>
<br/>
1) Create application
<p>The operation account is the application receiving account, which must be an freedom account. When transferring ownership, other attributes can be modified at the same time.</p>
<pre>
bindapp receive_account create APPID ... -p eosio.app -p receive_account
  
bindapp apponeowner1 create 1000 --has_memo --memo "test application" --has_expire --expire "2030-01-01T00:00:00" -p eosio.app -p apponeowner1
</pre>
<br/>
2) Transfer application ownership
<p>The operation account is the application receiving account, which must be an freedom account. When transferring ownership, other attributes can be modified at the same time.</p>
<pre>
bindapp receive_account transfer APPID ... -p eosio.app -p old_owner_account -p receive_account

bindapp apponeowner2 transfer 1000 --has_memo --memo "new application" --has_expire --expire "2020-01-01T00:00:00" -p eosio.app -p apponeowner1 -p apponeowner2
</pre>
<br/>
3) Application expired
<p>If the expiration time is set, after the application expires, application-related changes no longer require application account authorization. The application account should apply for extended usage time before it expires.</p>

3. Set the token properties
<p>The operation account, application account, and application administrator authorization are required.</p>
<pre>
bindsym &lt;account&gt; &lt;opr_code&gt; &lt;sym&gt;
account Operation account
opr_code operation
  modify modify token attributes
  transfer transfer token ownership
sym token symbol

--has_tollor modify tollor
--tollor charge account

--has_issuer modify issuer
--issuer issue account

--has_fee modify the charging rules
--minval start charge transfer amount
--minfee minimum fee
--level step span
--delta step difference
--maxfee maximum fee

Start charging when transfer amount >= minval,
  Fixed fee, when level == 0, fee = minfee
  Ladder fee, when level > 0, fee = (value-minval) / level * delta + minfee, fee <= maxfee
</pre>

1) Transfer token ownership
<p>The tokens are bound to the application and owned by the application. Modifying the token attributes requires application account authorization. The operation account is the token receiving account, which must be an application account. When transferring ownership, other attributes can be modified at the same time.</p>
<pre>
bindsym receive_account transfer TOKEN ... -p eosio.app -p old_app_account -p receive_account

// 4,GBTC
bindsym apponeowner3 transfer GBTC --has_tollor --tollor apponetollr3 --has_issuer --issuer apponeissue3 --has_fee --minval 1000000 --minfee 10 -p eosio.app -p apponeowner2 -p apponeowner3
</pre>

4. Query token properties
<pre>
get sym &lt;sym&gt;
sym token symbol
Return sym, appid, tollor, issuer, minval, minfee, level, delta, maxfee
</pre>

5. Query application properties
<pre>
get app &lt;appid&gt;
appid application id
Return appid, owner, created, expire, memo
</pre>

<h2>Extended contract instructions</h2>

1. Obtain the public chain local currency symbol
<pre>
uint64_t get_core_sym ()
Return core currency symbol and precision
</pre>

2. Get the charge
<pre>
name get_app_fee (uint64_t sym, int64_t value, int64_t* fee)
sym token symbol
value transfer amount
fee amount to be charged (output)
Return charge account
</pre>

3. Application account and issue account associated with tokens
<pre>
void new_app_sym (uint64_t sym, uint64_t owner, uint64_t issuer)
sym token symbol
owner application account
issuer issue account
</pre>

4. Get token issuer
<pre>
name get_sym_issuer (uint64_t sym)
sym token symbol
Return issuing account
</pre>

5. Create token
<p>Create tokens and bind them to application accounts and issue accounts.</p>
<pre>
void create2(name owner, name issuer, asset maximum_supply)
owner application account
issuer issue account
maximum_supply token asset

cleos push action eosio.token create2 '["apponeowner1","apponeissue1","10000000000.0000 GBTC"]' -p eosio.app -p apponeowner1
</pre>

