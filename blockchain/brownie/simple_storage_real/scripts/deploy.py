from brownie import network
from brownie import accounts
from brownie import SimpleStorage


def deploy_simple_storage():
    ## Using Ganache auto-generated accounts
    # account = accounts[0]

    ## Using brownie accounts to safely store an account
    ## `brownie accounts new freecodecamp-1`
    account=accounts.load("freecodecamp-1")
    print('account: ',account , type(account))

    ## Deploy the contract
    simple_storage = SimpleStorage.deploy({"from": account})
    print('simple_storage: ',simple_storage , type(simple_storage))

    ## some interactions with the contract
    stored_value = simple_storage.retrieve()
    print('stored_value: ',stored_value , type(stored_value))

    transaction = simple_storage.store(15, {"from": account})
    print('transaction: ',transaction , type(transaction))

    stored_value = simple_storage.retrieve()
    print('stored_value: ',stored_value , type(stored_value))


def get_account():
    if(network.show_active() == "development") :
        ## Using Ganache auto-generated accounts
        account = accounts[0]
        print('account: ',account , type(account))
        return account

    else:
        ## Using brownie accounts to safely store an account
        ## `brownie accounts new freecodecamp-1`
        account=accounts.load("freecodecamp-1")
        print('account: ',account , type(account))
        return account



def main():
    print("hello")
    deploy_simple_storage()
