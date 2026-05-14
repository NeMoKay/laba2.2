#include "httplib.h"
#include <nlohmann/json.hpp>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <functional>

using json = nlohmann::json;
std::mutex state_mutex;

std::unique_ptr<Sequence<int>> arr_seq = std::make_unique<ArraySequence<int>>();
std::unique_ptr<Sequence<int>> list_seq = std::make_unique<ListSequence<int>>();
std::unique_ptr<BitSequence<int>> bit_seq = std::make_unique<BitSequence<int>>();

inline int double_val(int x){ 
    return x * 2; 
}

inline bool is_big(int x){ 
    if (x > 60){
        return true;
    }
    else{
        return false;
    }
}

inline int sum_func(int acc, int x){ 
    return acc + x; 
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
    
    if (type == "array"){
        response["state"] = toJson(arr_seq.get());
    }
    else{
        if (type == "list"){
            response["state"] = toJson(list_seq.get());
        }
        else{
            if (type == "bit"){
                response["state"] = bitToJson(bit_seq.get());
            }
            else{
                response["state"] = json::array();
            }
        }
    }
    
    response["log"] = log;
    return response.dump();
}

void handle_action(const httplib::Request& req, httplib::Response& res, std::function<void(const json&, const std::string&, std::string&)> logic){
    std::lock_guard<std::mutex> lock(state_mutex);
    std::string log = "Success";
    std::string type = "array"; 
    
    try{
        auto body = json::parse(req.body);
        type = body.value("type", "array");
        logic(body, type, log);
    } 
    catch(const json::exception& e){
        log = std::string("JSON Parse Error: ") + e.what();
    } 
    catch(const std::exception& e){
        log = std::string("Error: ") + e.what();
    }
    
    res.set_content(build_response(type, log), "application/json");
}

int main(){
    httplib::Server svr;

    svr.set_mount_point("/", "./interface_html");

    svr.Get("/api/get_state", [](const httplib::Request& req, httplib::Response& res){
        std::lock_guard<std::mutex> lock(state_mutex);
        std::string type = req.get_param_value("type");
        res.set_content(build_response(type, "Retrieved State"), "application/json");
    });

    svr.Get("/api/clear", [](const httplib::Request& req, httplib::Response& res){
        std::lock_guard<std::mutex> lock(state_mutex);
        std::string type = req.get_param_value("type");
        
        if (type == "array"){
            arr_seq = std::make_unique<ArraySequence<int>>();
        }
        else{
            if (type == "list"){
                list_seq = std::make_unique<ListSequence<int>>();
            }
            else{
                if (type == "bit"){
                    bit_seq = std::make_unique<BitSequence<int>>();
                }
            }
        }
        
        res.set_content(build_response(type, "Cleared!"), "application/json");
    });

    svr.Post("/api/append", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            int val = body.value("val", 0);
            if (type == "array"){
                arr_seq->Append(val);
            }
            else{
                if (type == "list"){
                    list_seq->Append(val);
                }
                else{
                    if (type == "bit"){
                        bit_seq->Append(Bit<int>(val));
                    }
                }
            }
        });
    });

    svr.Post("/api/prepend", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            int val = body.value("val", 0);
            if (type == "array"){
                arr_seq->Prepend(val);
            }
            else{
                if (type == "list"){
                    list_seq->Prepend(val);
                }
                else{
                    if (type == "bit"){
                        bit_seq->Prepend(Bit<int>(val));
                    }
                }
            }
        });
    });

    svr.Post("/api/insert", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            int val = body.value("val", 0);
            size_t idx = body.value("idx", 0);
            if (type == "array"){
                arr_seq->InsertAt(val, idx);
            }
            else{
                if (type == "list"){
                    list_seq->InsertAt(val, idx);
                }
                else{
                    if (type == "bit"){
                        bit_seq->InsertAt(Bit<int>(val), idx);
                    }
                }
            }
        });
    });

    svr.Post("/api/get_first", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "array"){
                log = "First: " + std::to_string(arr_seq->GetFirst());
            }
            else{
                if (type == "list"){
                    log = "First: " + std::to_string(list_seq->GetFirst());
                }
                else{
                    if (type == "bit"){
                        if (static_cast<bool>(bit_seq->GetFirst())){
                            log = "First: 1";
                        }
                        else{
                            log = "First: 0";
                        }
                    }
                }
            }
        });
    });

    svr.Post("/api/get_last", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "array"){
                log = "Last: " + std::to_string(arr_seq->GetLast());
            }
            else{
                if (type == "list"){
                    log = "Last: " + std::to_string(list_seq->GetLast());
                }
                else{
                    if (type == "bit"){
                        if (static_cast<bool>(bit_seq->GetLast())){
                            log = "Last: 1";
                        }
                        else{
                            log = "Last: 0";
                        }
                    }
                }
            }
        });
    });

    svr.Post("/api/get", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            size_t idx = body.value("idx", 0);
            if (type == "array"){
                log = "Item: " + std::to_string(arr_seq->Get(idx));
            }
            else{
                if (type == "list"){
                    log = "Item: " + std::to_string(list_seq->Get(idx));
                }
                else{
                    if (type == "bit"){
                        if (static_cast<bool>(bit_seq->Get(idx))){
                            log = "Item: 1";
                        }
                        else{
                            log = "Item: 0";
                        }
                    }
                }
            }
        });
    });

    svr.Post("/api/concat", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "array"){
                ArraySequence<int> temp;
                if (body.contains("items")){
                    if (body["items"].is_array()){
                        for (int item_val : body["items"]){
                            temp.Append(item_val);
                        }
                    }
                }
                arr_seq->Concat(&temp);
            }
            else{
                if (type == "list"){
                    ArraySequence<int> temp;
                    if (body.contains("items")){
                        if (body["items"].is_array()){
                            for (int item_val : body["items"]){
                                temp.Append(item_val);
                            }
                        }
                    }
                    list_seq->Concat(&temp);
                }
                else{
                    if (type == "bit"){
                        BitSequence<int> temp;
                        if (body.contains("items")){
                            if (body["items"].is_array()){
                                for (int item_val : body["items"]){
                                    temp.Append(Bit<int>(item_val));
                                }
                            }
                        }
                        bit_seq->Concat(&temp);
                    }
                }
            }
        });
    });

    svr.Post("/api/subseq", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            size_t start = body.value("start", 0);
            size_t end = body.value("end", 0);
            if (type == "array"){
                std::unique_ptr<Sequence<int>> sub(arr_seq->GetSubsequence(start, end));
                log = "Subseq : " + toJson(sub.get()).dump(); 
            }
            else{
                if (type == "list"){
                    std::unique_ptr<Sequence<int>> sub(list_seq->GetSubsequence(start, end));
                    log = "Subseq : " + toJson(sub.get()).dump(); 
                }
                else{
                    if (type == "bit"){
                        std::unique_ptr<BitSequence<int>> sub(bit_seq->GetSubsequence(start, end));
                        log = "Subseq : " + bitToJson(sub.get()).dump(); 
                    }
                }
            }
        });
    });

    svr.Post("/api/reduce", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "array"){
                auto* arr_ptr = dynamic_cast<ArraySequence<int>*>(arr_seq.get());
                log = "Result: " + std::to_string(arr_ptr->Reduce(sum_func, 0));
            }
            else{
                if (type == "list"){
                    auto* list_ptr = dynamic_cast<ListSequence<int>*>(list_seq.get());
                    log = "Result: " + std::to_string(list_ptr->Reduce(sum_func, 0));
                }
            }
        });
    });

    svr.Post("/api/map", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "array"){
                auto* arr_ptr = dynamic_cast<ArraySequence<int>*>(arr_seq.get());
                arr_seq.reset(arr_ptr->Map(double_val));
            }
            else{
                if (type == "list"){
                    auto* list_ptr = dynamic_cast<ListSequence<int>*>(list_seq.get());
                    list_seq.reset(list_ptr->Map(double_val));
                }
            }
            log = "Applied Map (*2)";
        });
    });

    svr.Post("/api/where", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "array"){
                auto* arr_ptr = dynamic_cast<ArraySequence<int>*>(arr_seq.get());
                arr_seq.reset(arr_ptr->Where(is_big));
            }
            else{
                if (type == "list"){
                    auto* list_ptr = dynamic_cast<ListSequence<int>*>(list_seq.get());
                    list_seq.reset(list_ptr->Where(is_big));
                }
            }
            log = "Applied Where (>60)";
        });
    });

    svr.Post("/api/bit_not", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "bit"){
                bit_seq = std::make_unique<BitSequence<int>>(~(*bit_seq));
            }
        });
    });

    svr.Post("/api/bit_and", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "bit"){
                std::string mask = body.value("mask", "");
                BitSequence<int> maskSeq;
                for (char c : mask){
                    if (c == '1'){
                        maskSeq.Append(Bit<int>(1));
                    }
                    else{
                        maskSeq.Append(Bit<int>(0));
                    }
                }
                bit_seq = std::make_unique<BitSequence<int>>(*bit_seq & maskSeq);
            }
        });
    });

    svr.Post("/api/bit_or", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "bit"){
                std::string mask = body.value("mask", "");
                BitSequence<int> maskSeq;
                for (char c : mask){
                    if (c == '1'){
                        maskSeq.Append(Bit<int>(1));
                    }
                    else{
                        maskSeq.Append(Bit<int>(0));
                    }
                }
                bit_seq = std::make_unique<BitSequence<int>>(*bit_seq | maskSeq);
            }
        });
    });

    svr.Post("/api/bit_xor", [](const httplib::Request& req, httplib::Response& res){
        handle_action(req, res, [](const json& body, const std::string& type, std::string& log){
            if (type == "bit"){
                std::string mask = body.value("mask", "");
                BitSequence<int> maskSeq;
                for (char c : mask){
                    if (c == '1'){
                        maskSeq.Append(Bit<int>(1));
                    }
                    else{
                        maskSeq.Append(Bit<int>(0));
                    }
                }
                bit_seq = std::make_unique<BitSequence<int>>(*bit_seq ^ maskSeq);
            }
        });
    });

    std::cout << "\n============================================\n";
    std::cout << "http://localhost:8080";
    std::cout << "\n============================================\n";
    
    svr.listen("0.0.0.0", 8080);
    return 0;
}