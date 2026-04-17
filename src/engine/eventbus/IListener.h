//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_ILISTENER_H
#define CMATERIAL_ILISTENER_H


#include <vector>
#include <type_traits>

namespace cmaterial::event {
    class IEvent;

    class IHandler {
    public:
        enum Order {
            FIRST = 0,
            DEFAULT = 1,
            LAST = 2
        };

        virtual ~IHandler() = default;
        virtual void execute(IEvent* e) = 0;
        virtual const void* getEventType() const = 0;
        virtual Order getOrder() const = 0;
    };

    template<typename EventT, typename FuncT>
    class LambdaHandler : public IHandler {
        FuncT func;
        Order order;
    public:
        LambdaHandler(FuncT f, Order o) : func(std::move(f)), order(o) {}
        void execute(IEvent* e) override { func(static_cast<EventT*>(e)); }
        const void* getEventType() const override { return EventT::getStaticType(); }
        Order getOrder() const override { return order; }
    };

    class IListener {
    public:
        using Order = IHandler::Order;

        virtual ~IListener();

        const std::vector<IHandler*>& getHandlers() const;
        void _add_handler(IHandler* h);

        template<typename EventT, typename FuncT>
        int _do_bind(FuncT func, Order o) {
            this->_add_handler(new LambdaHandler<EventT, FuncT>(std::move(func), o));
            return 0;
        }

    protected:
        std::vector<IHandler*> handlers;
    };
}

#define GET_EH_MACRO(_1, _2, _3, NAME, ...) NAME
#define EXPAND(x) x

#define EVENTHANDLER_2(EventT, MethodName)                                                                             \
    int _h_##MethodName =                                                                                              \
            this->_do_bind<EventT>([this](EventT *e) { this->MethodName(e); }, cmaterial::event::IHandler::DEFAULT);

#define EVENTHANDLER_3(EventT, MethodName, OrderVal)                                                                   \
    int _h_##MethodName = this->_do_bind<EventT>([this](EventT *e) { this->MethodName(e); }, OrderVal);

#define EVENTHANDLER(...) EXPAND(GET_EH_MACRO(__VA_ARGS__, EVENTHANDLER_3, EVENTHANDLER_2)(__VA_ARGS__))


#endif // CMATERIAL_ILISTENER_H
