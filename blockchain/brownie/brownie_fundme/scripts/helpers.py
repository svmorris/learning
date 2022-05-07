from web3 import Web3
from brownie import network
from brownie import accounts
from brownie import MockV3Aggregator


DECIMALS = 18
STARTING_PRICE = 2000

def get_account():
    """ Get a different account on local and real blockchains """
    if network.show_active() == "development":
        return accounts[0]

    return accounts.load('freecodecamp-1')


def deploy_mocks(account):
    """ Deploy mock contracts on development networks """
    if len(MockV3Aggregator) <= 0:
        price_feed_address = MockV3Aggregator.deploy(
                DECIMALS,
                Web3.toWei(STARTING_PRICE, "ether"),
                {"from": account}
                ).address
    else:
        price_feed_address = MockV3Aggregator[-1].address

    return price_feed_address
