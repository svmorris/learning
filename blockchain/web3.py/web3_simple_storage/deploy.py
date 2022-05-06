"""
    Web3 interface for the simple_storage test program
"""
import os
import json
from web3 import Web3
from web3.middleware import geth_poa_middleware


from solcx import install_solc
from solcx import compile_standard
#
# install_solc("0.8.0")


with open("./SimpleStorage.sol", "r", encoding="UTF-8")as file:
    simple_storage_file = file.read()

print("Compiling contract...", end="", flush=True)
# Compile solidity
compiled_sol = compile_standard({
    "language": "Solidity",
    "sources": {
        "SimpleStorage.sol": {
            "content": simple_storage_file
            }
        },
    "settings": {
        "outputSelection": {
            "*": {
                "*": [ "abi", "metadata", "evm.bytecode", "evm.sourceMap" ]
                }
            }
        }
    }, solc_version="0.8.0")


# Safe the compiled file so we can work with it easier
with open("compiled.json", "w+", encoding="UTF-8")as file:
    json.dump(compiled_sol, file, indent=4)


# get bytecode
sol_bytecode = compiled_sol["contracts"]["SimpleStorage.sol"]["SimpleStorage"]["evm"][
                                                                 "bytecode"]["object"]


# get abi
abi = compiled_sol["contracts"]["SimpleStorage.sol"]["SimpleStorage"]["abi"]
print("done!")


print("Connecting to the blockchain...", end="", flush=True)
# connection to ganache (local) netork
# w3 = Web3(Web3.HTTPProvider("http://127.0.0.1:8545"))
# chain_id = 1337
# my_address = "0xC4d9094ED28161a3fA67D7359cfD4e0242f508c2"
# my_private_key = "0x2e665c1949f1ea13dbbcdc31a04cabfe9ea74f9e6c1e3cca34d8a065684365d2" # prob don't do this


# Connect to rinkeby
w3 = Web3(Web3.HTTPProvider("https://rinkeby.infura.io/v3/37f722315b3b4318b220ec8fcc37bcfb")) # rinkeby
w3.middleware_onion.inject(geth_poa_middleware, layer=0)
chain_id = 4
my_address = "0xEd441DBBE5210a33c422982385109213025CeaC1"
my_private_key = "0xac5568b084b926b083c22044817a89c90a121498f109de5e2b74154550a15f4e" # This is my genuine private key lol (with no money)
print("done!")



# create contract
SimpleStorage = w3.eth.contract(abi=abi, bytecode=sol_bytecode)



# get latest transaction count (for nonce)
nonce = w3.eth.getTransactionCount(my_address)


print("Deploying contract...", end="", flush=True)
# 1: build a transaction
transaction = SimpleStorage.constructor().buildTransaction(
        {"chainId": chain_id, "from": my_address, "nonce": nonce})

# 2: sign the transaction
signed_transaction = w3.eth.account.sign_transaction(transaction, private_key=my_private_key)

# 3: send a transaction
transaction_hash = w3.eth.send_raw_transaction(signed_transaction.rawTransaction)
transaction_receipt = w3.eth.wait_for_transaction_receipt(transaction_hash)
print("done!")

print("Running tests:")

print("\tCurrent cool number: ", end="", flush=True)
# Working with the contract
# Contract address
# Contract abi
simple_storage = w3.eth.contract(address=transaction_receipt.contractAddress , abi=abi)

# 2 ways to interact with a function 
# Call -> Simulate making the call and getting a return value (blue button in remix)
# Transact -> Actually make a state change (yellow or red button in remix)

# initial value of cool_number
print(simple_storage.functions.retrieve().call())


i = 1
while True:
    # get latest transaction count (for nonce)
    nonce = w3.eth.getTransactionCount(my_address)

    print("\tSetting new cool number...",  end="", flush=True)
    # In order to make actually change the "cool_number" on chain. We have to
    # build, sign and send a new transaction.
    store_transaction = simple_storage.functions.store(i).buildTransaction({
        "chainId": chain_id,
        "from": my_address,
        "nonce": nonce
        })
    signed_store_tx = w3.eth.account.sign_transaction(store_transaction, private_key=my_private_key)
    send_store_tx = w3.eth.send_raw_transaction(signed_store_tx.rawTransaction)
    transaction_receipt = w3.eth.wait_for_transaction_receipt(send_store_tx)
    print("done!")


    print("\tCurrent cool number: ", end="", flush=True)
    print(simple_storage.functions.retrieve().call())
    i = i + i+1
