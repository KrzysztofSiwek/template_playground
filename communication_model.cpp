#include<functional>
#include <iostream>
#include <tuple>

template<typename T>
using SetFunc = void(*)(T);

template<typename req_t, typename resp_t, SetFunc<req_t> setStrategy, typename rollback_t = req_t>
struct SetMesgs{
    using Req_t = req_t;
    using Resp_t = resp_t;
    using Rollback_t = rollback_t;
    constexpr static SetFunc<req_t> setFunc = setStrategy;
};

struct SetAReq{};
struct SetAResp{};
void setAStrategy(SetAReq){
    std::cout << "strategu a" << std::endl;
}
using SetAMesgs = SetMesgs<SetAReq, SetAResp, setAStrategy>;

struct SetBReq{};
struct SetBResp{};
void setBStrategy(SetBReq){
    std::cout << "strategy b" << std::endl;
}
using SetBMesgs = SetMesgs<SetBReq, SetBResp, setBStrategy>;

template<typename... Ts>
struct CommModel{
    template<typename MsgT>
    void handleReqSendResp(typename MsgT::Req_t msg){
        prepareReq(msg);
        MsgT::setFunc(msg);
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

int main(){
    CommModel<SetAMesgs, SetBMesgs> comm;
    SetAReq a;
    comm.handleReqSendResp<SetAMesgs>(a);
    SetBReq b;
    comm.handleReqSendResp<SetBMesgs>(b);
}
