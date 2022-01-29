#include<functional>
#include <iostream>
#include <tuple>

struct SetAReq{};
struct SetAResp{};
struct SetAMesgs{
    using Req_t = SetAReq;
    using Resp_t = SetAResp;
};

struct SetBReq{};
struct SetBResp{};
struct SetBMesgs{
    using Req_t = SetBReq;
    using Resp_t = SetBResp;
};

template<typename... Ts>
struct CommModel{
    template<typename MsgT>
    void handleReqSendResp(typename MsgT::Req_t msg, std::function<void(typename MsgT::Req_t)> strategy){
        prepareReq(msg);
        strategy(msg);
        std::get<typename MsgT::Req_t>(types) = msg;
        sendResp<typename MsgT::Resp_t>();
    }
    template<typename ReqT>
    void prepareReq(ReqT){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    template<typename RespT>
    void sendResp(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    std::tuple<typename Ts::Req_t...> types;
};

void setAStrategy(SetAReq){
    std::cout << "strategu a" << std::endl;
}

void setBStrategy(SetBReq){
    std::cout << "strategy b" << std::endl;
}

int main(){
    CommModel<SetAMesgs, SetBMesgs> comm;
    SetAReq a;
    comm.handleReqSendResp<SetAMesgs>(a, &setAStrategy);
    SetBReq b;
    comm.handleReqSendResp<SetBMesgs>(b, &setBStrategy);
}
