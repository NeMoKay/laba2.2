#include "httplib.h"
#include <nlohmann/json.hpp>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

int double_val(int x){
    return x * 2;
}

bool is_big(int x){
    return x > 60;
}

int sum_func(int acc, int x){
    return acc + x;
}

class ISequenceHandler{
public:
    virtual ~ISequenceHandler() = default;
    virtual void Append(int val) = 0;
    virtual void Prepend(int val) = 0;
    virtual void InsertAt(int val, size_t index) = 0;
    virtual void Concat(const json& items) = 0;
    virtual std::string GetFirst() = 0;
    virtual std::string GetLast() = 0;
    virtual std::string Get(size_t index) = 0;
    virtual json GetState() = 0;
    virtual void Map() = 0;
    virtual void Where() = 0;
    virtual std::string Reduce() = 0;
    virtual std::string Subsequence(size_t s, size_t e) = 0;
    virtual std::string BitNot() = 0;
    virtual std::string BitAnd(const std::string& mask) = 0;
    virtual std::string BitOr(const std::string& mask) = 0;
    virtual std::string BitXor(const std::string& mask) = 0;
};

template <typename Seq>
class StandardHandler : public ISequenceHandler{
    Seq* seq;
public:
    StandardHandler() : seq(new Seq()){
    }

    ~StandardHandler(){
        delete seq;
    }

    void Append(int v) override{
        seq->Append(v);
    }

    void Prepend(int v) override{
        seq->Prepend(v);
    }

    void InsertAt(int v, size_t i) override{
        seq->InsertAt(v, i);
    }

    void Concat(const json& items) override{
        for(auto& item : items){
            seq->Append(item.get<int>());
        }
    }

    std::string GetFirst() override{
        return std::to_string(seq->GetFirst());
    }

    std::string GetLast() override{
        return std::to_string(seq->GetLast());
    }

    std::string Get(size_t i) override{
        return std::to_string(seq->Get(i));
    }

    json GetState() override{
        json j = json::array();
        for(size_t i = 0; i < seq->GetLength(); i++){
            j.push_back(seq->Get(i));
        }
        return j;
    }

    void Map() override{
        auto next = ::Map(seq, double_val);
        delete seq;
        seq = next;
    }

    void Where() override{
        auto next = ::Where(seq, is_big);
        delete seq;
        seq = next;
    }

    std::string Reduce() override{
        return std::to_string(::Reduce(seq, sum_func, 0));
    }

    std::string Subsequence(size_t s, size_t e) override{
        auto sub = seq->GetSubsequence(s, e);
        json j = json::array();
        for(size_t i = 0; i < sub->GetLength(); i++){
            j.push_back(sub->Get(i));
        }
        delete sub;
        return j.dump();
    }

    std::string BitNot() override{
        return "Not supported";
    }

    std::string BitAnd(const std::string& mask) override{
        return "Not supported";
    }

    std::string BitOr(const std::string& mask) override{
        return "Not supported";
    }

    std::string BitXor(const std::string& mask) override{
        return "Not supported";
    }
};

class BitHandler : public ISequenceHandler{
    BitSequence<int>* seq;
    
    BitSequence<int> create_mask(const std::string& mask_str){
        BitSequence<int> m;
        for (char c : mask_str){
            m.Append(Bit<int>(c == '1' ? 1 : 0));
        }
        return m;
    }

public:
    BitHandler() : seq(new BitSequence<int>()){
    }

    ~BitHandler(){
        delete seq;
    }

    void Append(int v) override{
        seq->Append(Bit<int>(v));
    }

    void Prepend(int v) override{
        seq->Prepend(Bit<int>(v));
    }

    void InsertAt(int v, size_t i) override{
        seq->InsertAt(Bit<int>(v), i);
    }

    void Concat(const json& items) override{
        for(auto& item : items){
            seq->Append(Bit<int>(item.get<int>()));
        }
    }

    std::string GetFirst() override{
        return std::to_string(static_cast<bool>(seq->GetFirst()));
    }

    std::string GetLast() override{
        return std::to_string(static_cast<bool>(seq->GetLast()));
    }

    std::string Get(size_t i) override{
        return std::to_string(static_cast<bool>(seq->Get(i)));
    }

    json GetState() override{
        json j = json::array();
        for(size_t i = 0; i < seq->GetLength(); i++){
            j.push_back(static_cast<bool>(seq->Get(i)) ? 1 : 0);
        }
        return j;
    }

    void Map() override{
    }

    void Where() override{
    }

    std::string Reduce() override{
        return "0";
    }

    std::string Subsequence(size_t s, size_t e) override{
        auto sub = seq->GetSubsequence(s, e);
        json j = json::array();
        for(size_t i = 0; i < sub->GetLength(); i++){
            j.push_back(static_cast<bool>(sub->Get(i)) ? 1 : 0);
        }
        delete sub;
        return j.dump();
    }

    std::string BitNot() override{ 
        auto next = new BitSequence<int>(~(*seq)); 
        delete seq;
        seq = next; 
        return "Success"; 
    }

    std::string BitAnd(const std::string& mask) override{
        auto next = new BitSequence<int>((*seq) & create_mask(mask));
        delete seq;
        seq = next;
        return "Success";
    }

    std::string BitOr(const std::string& mask) override{
        auto next = new BitSequence<int>((*seq) | create_mask(mask));
        delete seq;
        seq = next;
        return "Success";
    }

    std::string BitXor(const std::string& mask) override{
        auto next = new BitSequence<int>((*seq) ^ create_mask(mask));
        delete seq;
        seq = next;
        return "Success";
    }
};

ISequenceHandler* arr_h = new StandardHandler<ArraySequence<int>>();
ISequenceHandler* list_h = new StandardHandler<ListSequence<int>>();
ISequenceHandler* bit_h = new BitHandler();

ISequenceHandler* get_h(const std::string& type){
    if (type == "list"){
        return list_h;
    }
    if (type == "bit"){
        return bit_h;
    }
    return arr_h;
}

std::string build_response(const std::string& type, const std::string& log){
    json response;
    try{
        response["state"] = get_h(type)->GetState();
    } catch (...){
        response["state"] = json::array();
    }
    response["log"] = log;
    return response.dump();
}

int main(){
    httplib::Server svr;
    svr.set_mount_point("/", "./interface_html");

    svr.Get("/api/get_state", [](const httplib::Request& req, httplib::Response& res){
        res.set_content(build_response(req.get_param_value("type"), "State"), "application/json");
    });

    svr.Get("/api/clear", [](const httplib::Request& req, httplib::Response& res){
        std::string type = req.get_param_value("type");
        if (type == "array"){
            delete arr_h;
            arr_h = new StandardHandler<ArraySequence<int>>();
        } else if (type == "list"){
            delete list_h;
            list_h = new StandardHandler<ListSequence<int>>();
        } else if (type == "bit"){
            delete bit_h;
            bit_h = new BitHandler();
        }
        res.set_content(build_response(type, "Cleared!"), "application/json");
    });

    auto handle = [](const httplib::Request& req, httplib::Response& res, auto action){
        auto b = json::parse(req.body);
        std::string type = b.value("type", "array");
        try{
            action(get_h(type), b);
            res.set_content(build_response(type, "Success"), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response(type, std::string("Error: ") + e.what()), "application/json");
        } catch (const std::exception& e){
            res.set_content(build_response(type, std::string("Internal Error: ") + e.what()), "application/json");
        }
    };

    svr.Post("/api/append", [&](const auto& req, auto& res){
        handle(req, res, [](auto h, auto b){
            h->Append(b.value("val", 0));
        });
    });

    svr.Post("/api/prepend", [&](const auto& req, auto& res){
        handle(req, res, [](auto h, auto b){
            h->Prepend(b.value("val", 0));
        });
    });

    svr.Post("/api/insert", [&](const auto& req, auto& res){
        handle(req, res, [](auto h, auto b){
            h->InsertAt(b.value("val", 0), b.value("index", 0));
        });
    });

    svr.Post("/api/concat", [&](const auto& req, auto& res){
        handle(req, res, [](auto h, auto b){
            h->Concat(b["items"]);
        });
    });

    svr.Post("/api/map", [&](const auto& req, auto& res){
        handle(req, res, [](auto h, auto b){
            h->Map();
        });
    });

    svr.Post("/api/where", [&](const auto& req, auto& res){
        handle(req, res, [](auto h, auto b){
            h->Where();
        });
    });

    svr.Post("/api/get", [](const auto& req, auto& res){
        auto b = json::parse(req.body);
        try{
            res.set_content(build_response(b["type"], "Item: " + get_h(b["type"])->Get(b.value("index", 0))), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response(b["type"], std::string("Error: ") + e.what()), "application/json");
        }
    });
    
    svr.Post("/api/get_first", [](const auto& req, auto& res){
        auto b = json::parse(req.body);
        try{
            res.set_content(build_response(b["type"], "First: " + get_h(b["type"])->GetFirst()), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response(b["type"], std::string("Error: ") + e.what()), "application/json");
        }
    });

    svr.Post("/api/get_last", [](const auto& req, auto& res){
        auto b = json::parse(req.body);
        try{
            res.set_content(build_response(b["type"], "Last: " + get_h(b["type"])->GetLast()), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response(b["type"], std::string("Error: ") + e.what()), "application/json");
        }
    });

    svr.Post("/api/reduce", [](const auto& req, auto& res){
        auto b = json::parse(req.body);
        try{
            res.set_content(build_response(b["type"], "Result: " + get_h(b["type"])->Reduce()), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response(b["type"], std::string("Error: ") + e.what()), "application/json");
        }
    });

    svr.Post("/api/subseq", [](const auto& req, auto& res){
        auto b = json::parse(req.body);
        try{
            res.set_content(build_response(b["type"], "Subseq: " + get_h(b["type"])->Subsequence(b.value("start", 0), b.value("end", 0))), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response(b["type"], std::string("Error: ") + e.what()), "application/json");
        }
    });

    svr.Post("/api/bit_not", [](const auto& req, auto& res){
        try{
            res.set_content(build_response("bit", get_h("bit")->BitNot()), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response("bit", std::string("Error: ") + e.what()), "application/json");
        }
    });

    svr.Post("/api/bit_and", [](const auto& req, auto& res){
        auto b = json::parse(req.body);
        try{
            res.set_content(build_response("bit", get_h("bit")->BitAnd(b.value("mask", ""))), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response("bit", std::string("Error: ") + e.what()), "application/json");
        }
    });

    svr.Post("/api/bit_or", [](const auto& req, auto& res){
        auto b = json::parse(req.body);
        try{
            res.set_content(build_response("bit", get_h("bit")->BitOr(b.value("mask", ""))), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response("bit", std::string("Error: ") + e.what()), "application/json");
        }
    });

    svr.Post("/api/bit_xor", [](const auto& req, auto& res){
        auto b = json::parse(req.body);
        try{
            res.set_content(build_response("bit", get_h("bit")->BitXor(b.value("mask", ""))), "application/json");
        } catch (const Exception& e){
            res.set_content(build_response("bit", std::string("Error: ") + e.what()), "application/json");
        }
    });

    std::cout << "\nhttp://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
    
    delete arr_h; 
    delete list_h; 
    delete bit_h;
    
    return 0;
}