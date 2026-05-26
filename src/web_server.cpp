#include "httplib.h"
#include <nlohmann/json.hpp>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

Sequence<int>* arr_seq = new ArraySequence<int>();
Sequence<int>* list_seq = new ListSequence<int>();
BitSequence<int>* bit_seq = new BitSequence<int>();

int double_val(int x){
    return x * 2; 
}

bool is_big(int x){ 
    return x > 60;
}

int sum_func(int acc, int x){ 
    return acc + x; 
}

Sequence<int>* get_seq(const std::string& type){
    if (type == "list"){
        return list_seq;
    } 
    else{
        return arr_seq;
    }
}

json toJson(const Sequence<int>* seq){
    json j = json::array();
    if (seq){
        for(size_t i = 0; i < seq->GetLength(); i++){
            j.push_back(seq->Get(i));
        }
    }
    return j;
}

json bitToJson(const BitSequence<int>* seq){
    json j = json::array();
    if (seq){
        for(size_t i = 0; i < seq->GetLength(); i++){
            if (static_cast<bool>(seq->Get(i))){
                j.push_back(1);
            } 
            else{
                j.push_back(0);
            }
        }
    }
    return j;
}

std::string build_response(const std::string& type, const std::string& log){
    json response;
    
    if (type == "bit"){
        response["state"] = bitToJson(bit_seq);
    } 
    else{
        response["state"] = toJson(get_seq(type));
    }
    
    response["log"] = log;
    return response.dump();
}

int main(){
    httplib::Server svr;
    svr.set_mount_point("/", "./interface_html");

    svr.Get("/api/get_state", [](const httplib::Request& req, httplib::Response& res){
        std::string type = req.get_param_value("type");
        if (type.empty()){
            type = "array";
        }
        res.set_content(build_response(type, "Retrieved State"), "application/json");
    });

    svr.Get("/api/clear", [](const httplib::Request& req, httplib::Response& res){
        std::string type = req.get_param_value("type");
        if (type == "array"){
            delete arr_seq;
            arr_seq = new ArraySequence<int>();
        } 
        else if (type == "list"){
            delete list_seq;
            list_seq = new ListSequence<int>();
        } 
        else if (type == "bit"){
            delete bit_seq;
            bit_seq = new BitSequence<int>();
        }
        res.set_content(build_response(type, "Cleared!"), "application/json");
    });

    svr.Post("/api/append", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            int val = body.value("val", 0);
            
            if (type == "bit"){
                bit_seq->Append(Bit<int>(val));
            } 
            else{
                get_seq(type)->Append(val);
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/prepend", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            int val = body.value("val", 0);
            
            if (type == "bit"){
                bit_seq->Prepend(Bit<int>(val));
            } 
            else{
                get_seq(type)->Prepend(val);
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/insert", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            int val = body.value("val", 0);
            size_t idx = body.value("idx", 0);
            
            if (type == "bit"){
                bit_seq->InsertAt(Bit<int>(val), idx);
            } 
            else{
                get_seq(type)->InsertAt(val, idx);
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/get_first", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            
            if (type == "bit"){
                log = "First: " + std::to_string(static_cast<bool>(bit_seq->GetFirst()));
            } 
            else{
                log = "First: " + std::to_string(get_seq(type)->GetFirst());
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/get_last", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            
            if (type == "bit"){
                log = "Last: " + std::to_string(static_cast<bool>(bit_seq->GetLast()));
            } 
            else{
                log = "Last: " + std::to_string(get_seq(type)->GetLast());
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/get", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            size_t idx = body.value("idx", 0);
            
            if (type == "bit"){
                log = "Item: " + std::to_string(static_cast<bool>(bit_seq->Get(idx)));
            } 
            else{
                log = "Item: " + std::to_string(get_seq(type)->Get(idx));
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/subseq", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            size_t start = body.value("start", 0);
            size_t end = body.value("end", 0);
            
            if (type == "bit"){
                BitSequence<int>* sub = bit_seq->GetSubsequence(start, end);
                log = "Subseq: " + bitToJson(sub).dump(); 
                delete sub;
            } 
            else{
                Sequence<int>* sub = get_seq(type)->GetSubsequence(start, end);
                log = "Subseq: " + toJson(sub).dump(); 
                delete sub;
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/reduce", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            
            if (type == "array"){
                log = "Result: " + std::to_string(Reduce(static_cast<ArraySequence<int>*>(arr_seq), sum_func, 0));
            } 
            else if (type == "list"){
                log = "Result: " + std::to_string(Reduce(static_cast<ListSequence<int>*>(list_seq), sum_func, 0));
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/map", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            
            if (type == "array"){
                auto new_seq = Map(static_cast<ArraySequence<int>*>(arr_seq), double_val);
                delete arr_seq;
                arr_seq = new_seq;
            } 
            else if (type == "list"){
                auto new_seq = Map(static_cast<ListSequence<int>*>(list_seq), double_val);
                delete list_seq;
                list_seq = new_seq;
            }
            log = "Applied Map (*2)";
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/where", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            
            if (type == "array"){
                auto new_seq = Where(static_cast<ArraySequence<int>*>(arr_seq), is_big);
                delete arr_seq;
                arr_seq = new_seq;
            } 
            else if (type == "list"){
                auto new_seq = Where(static_cast<ListSequence<int>*>(list_seq), is_big);
                delete list_seq;
                list_seq = new_seq;
            }
            log = "Applied Where (>60)";
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    svr.Post("/api/bit_not", [](const httplib::Request& req, httplib::Response& res){
        std::string log = "Success";
        std::string type = "array"; 
        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            
            if(type == "bit"){
                auto new_seq = new BitSequence<int>(~(*bit_seq));
                delete bit_seq;
                bit_seq = new_seq;
            }
        } 
        catch(const std::exception& e){
            log = std::string("Error: ") + e.what();
        }
        res.set_content(build_response(type, log), "application/json");
    });

    std::cout << "\nhttp://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);

    delete arr_seq;
    delete list_seq;
    delete bit_seq;
    
    return 0;
}