module Player; 

import <map>;
import <memory>;
import <string>;
import <vector>;
import <iostream>;

import Ability; 
import Enums; 
import Link;


Player::Player(int playerNum) : playerNum{playerNum} {}

void Player::downloadLink(Link* link) {
    downloadedLinks.emplace_back(link);
    link->download();
    if (link->getType() == LinkType::DATA) {
        downloadedData++;
    } else if (link->getType() == LinkType::VIRUS) {
        downloadedVirus++;
    }
}

void Player::decrementAbilityCount() {
    abilitiesLeft--;
    if (abilitiesLeft <= 0) abilitiesLeft = 0;
}

bool Player::hasWon() const {
    return downloadedData >= 4;
}

bool Player::hasLost() const {
    return downloadedVirus >= 4;
}

void Player::revealOpponentLink(char c, int strength, LinkType type) {
    std::string id = (type == LinkType::DATA ? "D" : "V") + std::to_string(strength);
    knownOpponentLinks[c] = id;
}

std::string Player::getOpponentLinkInfo(char c) const {
    return knownOpponentLinks.at(c);
}

bool Player::knowsOpponentLink(char c) const {
    return knownOpponentLinks.find(c) != knownOpponentLinks.end();
}

int Player::getPlayerNum() const {
    return playerNum;
}

int Player::getDataDownloaded() const {
    return downloadedData; 
}

int Player::getVirusDownloaded() const {
    return downloadedVirus; 
}

int Player::getAbilitiesLeft() const {
    return abilitiesLeft; 
}

int Player::getTotalDownloaded() const {
    return downloadedData + downloadedVirus; 
}

Link* Player::getLinkByKey(char c) const {
    if (linkMap.find(c) != linkMap.end()) {
        std::string id = linkMap.at(c);
        for (const auto& link : allLinks) {
            if (link->getId() == id) {
                return link.get();
            }
        }
    }
    return nullptr; // Not found
}

void Player::updateLinkMap(char c) {
    Link* link = getLinkByKey(c);
    if (link) {
        linkMap[c] = link->getId();
    }
}

std::map<char, std::string>& Player::getLinkMap() {
    return linkMap;
}

std::map<char, std::string>& Player::getOpponentLinkMap() {
    return knownOpponentLinks;
}

std::vector<std::unique_ptr<Link>>& Player::getAllLinks() {
    return allLinks;
}

std::vector<std::unique_ptr<Ability>>& Player::getAbilities() {
    return abilities;
}

void Player::displayAbilities() {
    std::cout << "Player " << playerNum << " Abilities Left: " << abilitiesLeft << "\n";
    for (int i = 0; i < static_cast<int>(abilities.size()); i++) {
        std::cout << i+1 << ": " << abilities[i]->getName();
        if (abilities[i]->isUsed()) {
            std::cout << " (Used)";
        }
        std::cout << "\n";
    }
}

std::ostream& operator<<(std::ostream& out, const Player& player){
    out << "Player " << player.getPlayerNum() << ":" << std::endl;
    out << "Downloaded: " << player.getDataDownloaded() << "D, " << player.getVirusDownloaded() << "V" << std::endl;
    out << "Abilities: " << player.getAbilitiesLeft() << std::endl;
    int count = 0;
    for (const auto& pair: player.linkMap) {
        out << pair.first << ": " << pair.second; 
        if (count == 3) out << std::endl; 
        else out << "    ";
        count++;
    }
    return out;
}
