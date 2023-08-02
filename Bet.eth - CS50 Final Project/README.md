# Bet.eth
#### Video Demo: https://www.youtube.com/watch?v=_DpZG_2FEOU
#### Description:
#### Bet.eth is a platform that allows you to quickly place bets with friends and family. Ever been challenged to a game of rock-paper-scissors, or a push-up contest? Bet.eth allows those bold claims to be put to the test by putting money on the line. The application leverages Ethereum's blockchain-based smart contract technology to securely hold funds from both parties and automatically pays out to the bet winner. The winner is determined by the players themselves; if both agree on the result, the named winner receives the winnings. If there is a disagreement, however, the funds are automatically split, with each half returned to the respective player.

App.js: The server backend for the project, providing all routes for the various HTML files. Originally, the server was implemented using Python and Flask, but the integration of Metamask (wallet) required a transition to the frontend library web3.js, leading to the adoption of express.js. This shift posed an initial challenge but ultimately led to a rewarding learning experience.

Betting.sol: This smart contract code is written in Solidity, Ethereum's programming language. It includes various functions to facilitate bet creation, joining, and winner submission for payout. Programming for the blockchain necessitates efficiency considerations, given the role of 'gas' in executing any blockchain action. This focus on efficiency matches well with my own inclination towards optimization.

ReentrancyGuard.sol: An open-source contract with security features that my application inherits to guard against potential attacks.

public/betting_abi.js: Contains the Application Binary Interface (ABI) of the deployed smart contract. The ABI outlines the structure of the smart contract and is essential for frontend interaction. It is kept in a separate file for readability.

public/contract_address.js: Holds the address of my deployed smart contract. This information is kept separately for security purposes.

index.html, createbet.html, joinbet.html, submitwinner.html: These HTML files correspond to different pages of the application and comprise a mix of HTML, JavaScript, and CSS code. Future improvements could include more effective implementation of inheritance to reduce code repetition. I did attempt the implementation a few times but it kept interfering with my blockchain interactions
so I decided to move on.

styles.css: Contains the website's stylistic elements. The project has taught me how to utilize open-source templates from libraries like Bootstrap, a skill I'm eager to contribute back to the community.

favicon.ico: As a betting app, it's only fitting my icon is cash money!!