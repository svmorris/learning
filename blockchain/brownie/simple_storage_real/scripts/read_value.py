from brownie import config
from brownie import accounts
from brownie import SimpleStorage


def read_contract():
    simple_storage = SimpleStorage[-1]
    print('simple_storage: ',simple_storage , type(simple_storage))
    stored_value = simple_storage.retrieve()
    print('stored_value: ',stored_value , type(stored_value))

def main():
    read_contract()
