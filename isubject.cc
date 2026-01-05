export module ISubject;

import <vector>;
import IObserver;

using namespace std;

export class ISubject {
    protected:
        vector<IObserver *> displays;

    public:
        virtual ~ISubject() = default;
        void attach(IObserver* o);
        void detach(IObserver* o);
        void notifyObservers();
};
