""" Deploy script """

from brownie import FundMe #pylint: disable=import-error

from brownie import config #pylint: disable=import-error
from brownie import network #pylint: disable=import-error
from brownie import accounts #pylint: disable=import-error

from scripts.helpers import get_account #pylint: disable=import-error
from scripts.helpers import deploy_mocks #pylint: disable=import-error



def deploy_fund_me():
    """ Deploy the fundme contract """
    account = get_account()

    # If we are using rinkeby
    if network.show_active() != "development":
        price_feed_address = config["networks"][network.show_active()]["eth_usd_pricefeed_address"]

    # On dev blockchain we can deploy a mock price-feed
    else:
        price_feed_address = deploy_mocks(account)


    fund_me = FundMe.deploy(price_feed_address, {"from": account})

    print('fund_me: ',fund_me , type(fund_me))


def main():
    """ main """
    deploy_fund_me()
