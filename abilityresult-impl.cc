module AbilityResult; 

import Link;
import Square;

AbilityResult AbilityResult::failure() {
    return {};
}

AbilityResult AbilityResult::scan(Link* link) {
    if (link->isDownloaded()) return AbilityResult::failure();
    return {.success = true, .linkScanned = true, .linkSelected = link};
}

AbilityResult AbilityResult::polarize(Link* link) {
    if (link->isDownloaded()) return AbilityResult::failure();
    return {.success = true, .linkPolarized = true, .linkSelected = link};
}

AbilityResult AbilityResult::download(Link* link, int player) {
    if (link->isDownloaded() || link->getOwner() == player) return AbilityResult::failure();
    return {.success = true, .linkDownloaded = true, .linkSelected = link, .playerAffected = player};
}

AbilityResult AbilityResult::linkBoost(Link* link, int player) {
    if (link->isDownloaded() || link->getOwner() != player) return AbilityResult::failure();
    return {.success = true, .linkBoosted = true, .linkSelected = link, .playerAffected = player};
}

AbilityResult AbilityResult::diagonal(Link* link, int player) {
    if (link->isDownloaded() || link->getOwner() != player) return AbilityResult::failure();
    return {.success = true, .linkDiagonalized = true, .linkSelected = link, .playerAffected = player};
}

AbilityResult AbilityResult::swap(Link* link1, Link* link2, int player) {
    if (link1->isDownloaded() || link2->isDownloaded() || link1->getOwner() == link2->getOwner() || link1->getStrength() != link2->getStrength()) {
        return AbilityResult::failure();
    }
    return {.success = true, .linksSwapped = true, .linkSelected = link1, .linkToSwap = link2, .playerAffected = player};
}

AbilityResult AbilityResult::firewall(Square* square) {
    if (!square->isEmpty() || square->isFirewall() || square->isServerPort() || square->isBarrier()) {
        return AbilityResult::failure();
    }
    return {.success = true, .squareFirewalled = true, .squareSelected = square};
}

AbilityResult AbilityResult::barrier(Square* square) {
    if (!square->isEmpty() || square->isFirewall() || square->isServerPort() || square->isBarrier()) {
        return AbilityResult::failure();
    }
    return {.success = true, .squareBarriered = true, .squareSelected = square};
}
