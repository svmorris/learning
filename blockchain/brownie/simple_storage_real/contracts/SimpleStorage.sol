// SPDX-License-Identifier: MIT

pragma solidity >=0.6.0 <0.9.0;

contract SimpleStorage {

    uint256 cool_number;

    struct People {
        uint256 cool_numberber;
        string name;
    }

    People[] public people;
    mapping(string => uint256) public name_to_number;

    // Store a new cool number
    function store(uint256 _cool_number) public {
        cool_number = _cool_number;
    }

    function retrieve() public view returns (uint256){
        return cool_number;
    }

    function add_person(string memory _name, uint256 _cool_number) public {
        people.push(People(_cool_number, _name));
        name_to_number[_name] = _cool_number;
    }
}

