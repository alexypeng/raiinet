export module IObserver;

using namespace std;

export class IObserver {
    public:
        virtual ~IObserver() = default;
        virtual void notify() = 0;
};
