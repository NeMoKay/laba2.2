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

using json = nlohmann::json;
std::mutex state_mutex;

std::unique_ptr<ArraySequence<int>> arr_seq = std::make_unique<ArraySequence<int>>();
std::unique_ptr<ListSequence<int>> list_seq = std::make_unique<ListSequence<int>>();
std::unique_ptr<BitSequence<int>> bit_seq = std::make_unique<BitSequence<int>>();

int mapMult2(int x){
    return x * 2;
}

bool isEven(int x){
    return x % 2 == 0;
}

int reduceSum(int acc, int x){
    return acc + x;
}

json toJson(const Sequence<int>* seq){
    json j = json::array();
    if (seq != nullptr){
        for (size_t i = 0; i < seq->GetLength(); ++i){
            j.push_back(seq->Get(i));
        }
    }
    return j;
}

json bitToJson(const BitSequence<int>* seq){
    json j = json::array();
    if (seq != nullptr){
        for (size_t i = 0; i < seq->GetLength(); ++i){
            if (static_cast<bool>(seq->Get(i))){
                j.push_back(1);
            } else{
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
    else if (type == "list"){
        response["state"] = toJson(list_seq.get());
    } 
    else if (type == "bit"){
        response["state"] = bitToJson(bit_seq.get());
    } 
    else{
        response["state"] = json::array();
    }
    response["log"] = log;
    return response.dump();
}

void handleArrayOrListAction(const std::string& type, const std::string& act,
                             int val, size_t idx, size_t start, size_t end,
                             const std::vector<int>& items, std::string& log){
    Sequence<int>* s = nullptr;
    if (type == "array"){
        s = static_cast<Sequence<int>*>(arr_seq.get());
    } 
    else{
        s = static_cast<Sequence<int>*>(list_seq.get());
    }

    if (act == "append"){
        s->Append(val);
    } 
    else if (act == "prepend"){
        s->Prepend(val);
    } 
    else if (act == "insert"){
        s->InsertAt(val, idx);
    } 
    else if (act == "get_first"){
        log = "First: " + std::to_string(s->GetFirst());
    } 
    else if (act == "get_last"){
        log = "Last: " + std::to_string(s->GetLast());
    } 
    else if (act == "get"){
        log = "Item: " + std::to_string(s->Get(idx));
    } 
    else if (act == "concat"){
        ArraySequence<int> temp;
        for (int item_val : items){
            temp.Append(item_val);
        }
        s->Concat(&temp);
    } 
    else if (act == "subseq"){
        std::unique_ptr<Sequence<int>> sub(s->GetSubsequence(start, end));
        log = "Subseq : " + toJson(sub.get()).dump();
    } 
    else if (act == "reduce"){
        int result = 0;
        if (type == "array"){
            result = arr_seq->Reduce(reduceSum, 0);
        } else{
            result = list_seq->Reduce(reduceSum, 0);
        }
        log = "Result: " + std::to_string(result);
    } 
    else if (act == "map" || act == "where"){
        if (type == "array"){
            Sequence<int>* result = nullptr;
            if (act == "map"){
                result = arr_seq->Map(mapMult2);
            } else{
                result = arr_seq->Where(isEven);
            }
            arr_seq.reset(dynamic_cast<ArraySequence<int>*>(result));
        } 
        else{
            Sequence<int>* result = nullptr;
            if (act == "map"){
                result = list_seq->Map(mapMult2);
            } else{
                result = list_seq->Where(isEven);
            }
            list_seq.reset(dynamic_cast<ListSequence<int>*>(result));
        }
        log = "Applied " + act;
    }
}

void handleBitAction(const std::string& act, int val, size_t idx, size_t start, size_t end,
                     const std::string& mask, const std::vector<int>& items, std::string& log){
    BitSequence<int>* b = bit_seq.get();

    if (act == "append"){
        b->Append(Bit<int>(val));
    } 
    else if (act == "prepend"){
        b->Prepend(Bit<int>(val));
    } 
    else if (act == "insert"){
        b->InsertAt(Bit<int>(val), idx);
    } 
    else if (act == "get_first"){
        if (static_cast<bool>(b->GetFirst())){
            log = "First: 1";
        } else{
            log = "First: 0";
        }
    } 
    else if (act == "get_last"){
        if (static_cast<bool>(b->GetLast())){
            log = "Last: 1";
        } else{
            log = "Last: 0";
        }
    } 
    else if (act == "get"){
        if (static_cast<bool>(b->Get(idx))){
            log = "Item: 1";
        } else{
            log = "Item: 0";
        }
    } 
    else if (act == "concat"){
        BitSequence<int> temp;
        for (int item_val : items){
            temp.Append(Bit<int>(item_val));
        }
        b->Concat(&temp);
    } 
    else if (act == "subseq"){
        std::unique_ptr<BitSequence<int>> sub(b->GetSubsequence(start, end));
        log = "Subseq : " + bitToJson(sub.get()).dump();
    } 
    else if (act == "bit_not"){
        bit_seq = std::make_unique<BitSequence<int>>(~(*b));
    } 
    else if (act == "bit_and" || act == "bit_or" || act == "bit_xor"){
        BitSequence<int> maskSeq;
        for (char c : mask){
            if (c == '1'){
                maskSeq.Append(Bit<int>(1));
            } else{
                maskSeq.Append(Bit<int>(0));
            }
        }
        if (act == "bit_and"){
            bit_seq = std::make_unique<BitSequence<int>>(*b & maskSeq);
        } 
        else if (act == "bit_or"){
            bit_seq = std::make_unique<BitSequence<int>>(*b | maskSeq);
        } 
        else if (act == "bit_xor"){
            bit_seq = std::make_unique<BitSequence<int>>(*b ^ maskSeq);
        }
    }
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
        else if (type == "list"){
            list_seq = std::make_unique<ListSequence<int>>();
        } 
        else if (type == "bit"){
            bit_seq = std::make_unique<BitSequence<int>>();
        }
        res.set_content(build_response(type, "Cleared!"), "application/json");
    });

    svr.Post("/api/action", [](const httplib::Request& req, httplib::Response& res){
        std::lock_guard<std::mutex> lock(state_mutex);
        std::string log = "Success";
        std::string type = "array";

        try{
            auto body = json::parse(req.body);
            type = body.value("type", "array");
            std::string act = body.value("act", "");
            int val = body.value("val", 0);
            size_t idx = body.value("idx", 0);
            size_t start = body.value("start", 0);
            size_t end = body.value("end", 0);
            std::string mask = body.value("mask", "");
            std::vector<int> items;
            if (body.contains("items") && body["items"].is_array()){
                for (int item_val : body["items"]){
                    items.push_back(item_val);
                }
            }

            if (type == "array" || type == "list"){
                handleArrayOrListAction(type, act, val, idx, start, end, items, log);
            } 
            else if (type == "bit"){
                handleBitAction(act, val, idx, start, end, mask, items, log);
            } 
            else{
                log = "Unknown sequence type";
            }
        } catch (const json::exception& e){
            log = std::string("JSON Parse Error: ") + e.what();
        } catch (const std::exception& e){
            log = std::string("Error: ") + e.what();
        }

        res.set_content(build_response(type, log), "application/json");
    });

    std::cout << "\n============================================\n";
    std::cout << "SERVER STARTED ON: http://localhost:8080\n";
    std::cout << "Open this URL in your browser.\n";
    std::cout << "Press Ctrl+C to stop.\n";
    std::cout << "============================================\n\n";

    svr.listen("0.0.0.0", 8080);
    return 0;
}