// SPDX-License-Identifier: MIT

pragma solidity 0.8.20;

import "./ReentrancyGuard.sol";

contract Betting is ReentrancyGuard {

    string betDescription;
    uint256 betAmount;
    address payable p1;
    address payable p2;

    mapping(address => uint8) public playerSelections;
    bool public isBetInProgress;
    bool public p2JoinedBet;

    event BetCreated(string betDescription, uint256 amount, address indexed betCreator);
    event BetJoined(address indexed betInvitee);
    event WinnerPaid(uint8 winner, uint256 amount, address indexed winnerAddress);
    event FundsReturned(address indexed p1Address, address indexed p2Address, uint256 amount);


    function createBet(string memory _betDescription, uint256 _betAmount) public payable nonReentrant {

        require(msg.value == _betAmount, "Value of funds sent is incorrect");
        require(isBetInProgress == false, "Bet is already in progress, you must wait");

        // Set values to global variables
        betDescription = _betDescription;
        betAmount = _betAmount;
        p1 = payable(msg.sender);

        // Update isBetInProgress variable
        isBetInProgress = true;

        emit BetCreated(_betDescription, _betAmount, msg.sender);
    }


    function joinBet() public payable nonReentrant {

        require(msg.value == betAmount, "Value of funds sent is incorrect");
        // Ensure P1 doesn't try to join their own bet
        require(msg.sender != p1, "P1, do not try to join your own bet");
        // Ensure P2 doesn't call joinBet function more than once
        require(p2 == address(0), "Bet already joined");

        // Update p2 variable with p2 address
        p2 = payable(msg.sender);

        // Update p2JoinedBet variable
        p2JoinedBet = true;

        emit BetJoined(p2);
    }


    function submitWinner(uint8 _chosenWinner) public nonReentrant {

        require(msg.sender == p1 || msg.sender == p2, "Only a player can submit a winner");
        require(p2JoinedBet, "p2 hasn't joined bet yet");
        require(_chosenWinner == 1 || _chosenWinner == 2, "Invalid winner selection");
        // Ensure the player hasn't already submitted a winner. Prevents multiple entries from a player or changing choice
        require(playerSelections[msg.sender] == 0, "You have already submitted a winner, ya donkey!");

        // Update players' selections in mapping
        playerSelections[msg.sender] = _chosenWinner;

        // Once both players have submitted Winners, execute below
        if (playerSelections[p1] != 0 && playerSelections[p2] != 0) {
            payWinner();
        }
    }


    function payWinner() internal {

        // Escrow balance
        uint256 contractBalance = address(this).balance;

        // Both players chose the same winner
        if(playerSelections[p1] == playerSelections[p2]) {
            if(playerSelections[p1] == 1) {
                (bool success, ) = payable(address(p1)).call{value: contractBalance}("");
                require(success, "Payment to winner P1 failed");

                emit WinnerPaid(1, contractBalance, address(p1));
            }
            else {
                (bool success, ) = payable(address(p2)).call{value: contractBalance}("");
                require(success, "Payment to winner P2 failed");

                emit WinnerPaid(2, contractBalance, address(p2));
            }
        }
        // Players couldn't agree on winner, money returned
        else {
            (bool success, ) = payable(address(p1)).call{value: (contractBalance / 2)}("");
            require(success, "Returning funds to P1 failed");
            (bool success2, ) = payable(address(p2)).call{value: (contractBalance / 2)}("");
            require(success2, "Returning funds to P2 failed");

            emit FundsReturned(address(p1), address(p2), contractBalance / 2);
        }

        // Reset state for next bet
        isBetInProgress = false;
        p2JoinedBet = false;
        delete playerSelections[p1];
        delete playerSelections[p2];
        delete betDescription;
        delete betAmount;
        delete p1;
        delete p2;
    }
}