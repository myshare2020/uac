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
</pre>
Use the uac files to overwrite the files in the corresponding directories.



