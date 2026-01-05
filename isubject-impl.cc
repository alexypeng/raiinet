module ISubject;

import <algorithm>;

using namespace std;

void ISubject::attach(IObserver* o) {
    displays.push_back(o);
}

void ISubject::detach(IObserver* o) {
    auto it = find(displays.begin(), displays.end(), o);
    if (it != displays.end()) {
        displays.erase(it);
    }
}

void ISubject::notifyObservers() {
    for (auto observer : displays) {
        observer->notify();
    }
}
