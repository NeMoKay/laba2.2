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

int sum_func(int accumulator, int x){
    return accumulator + x;
}

class ISequenceHandler{
public:
    virtual ~ISequenceHandler() = default;

    virtual void Append(int value) = 0;
    virtual void Prepend(int value) = 0;
    virtual void InsertAt(int value, size_t index) = 0;
    virtual void Concat(const json& items) = 0;

    virtual std::string GetFirst() = 0;
    virtual std::string GetLast() = 0;
    virtual std::string Get(size_t index) = 0;
    virtual json GetState() = 0;
    virtual void Map() = 0;
    virtual void Where() = 0;

    virtual std::string Reduce() = 0;
    virtual std::string Subsequence(size_t start_index, size_t end_index) = 0;
    virtual std::string BitNot() = 0;
    virtual std::string BitAnd(const std::string& mask_string) = 0;
    virtual std::string BitOr(const std::string& mask_string) = 0;
    virtual std::string BitXor(const std::string& mask_string) = 0;
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

    void Append(int value) override{
        seq->Append(value);
    }

    void Prepend(int value) override{
        seq->Prepend(value);
    }

    void InsertAt(int value, size_t index) override{
        seq->InsertAt(value, index);
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

    std::string Get(size_t index) override{
        return std::to_string(seq->Get(index));
    }

    json GetState() override{
        json json_state = json::array();
        for(size_t index = 0; index < seq->GetLength(); index++){
            json_state.push_back(seq->Get(index));
        }
        return json_state;
    }

    void Map() override{
        auto next_sequence = ::Map(seq, double_val);
        delete seq;
        seq = next_sequence;
    }

    void Where() override{
        auto next_sequence = ::Where(seq, is_big);
        delete seq;
        seq = next_sequence;
    }

    std::string Reduce() override{
        return std::to_string(::Reduce(seq, sum_func, 0));
    }

    std::string Subsequence(size_t start_index, size_t end_index) override{
        auto sub_sequence = seq->GetSubsequence(start_index, end_index);
        json json_state = json::array();
        for(size_t index = 0; index < sub_sequence->GetLength(); index++){
            json_state.push_back(sub_sequence->Get(index));
        }
        delete sub_sequence;
        return json_state.dump();
    }

    std::string BitNot() override{
        return "Not supported";
    }

    std::string BitAnd(const std::string& mask_string) override{
        return "Not supported";
    }

    std::string BitOr(const std::string& mask_string) override{
        return "Not supported";
    }

    std::string BitXor(const std::string& mask_string) override{
        return "Not supported";
    }
};

class BitHandler : public ISequenceHandler{
    BitSequence<int>* seq;
    
    BitSequence<int> create_mask(const std::string& mask_string){
        BitSequence<int> value_mask;
        
        for (char character : mask_string){
            int bit_value;

            if (character == '1'){
                bit_value = 1;
            } 
            else{
                bit_value = 0;
            }

            value_mask.Append(Bit<int>(bit_value));
        }
        return value_mask;
    }

public:
    BitHandler() : seq(new BitSequence<int>()){
    }

    ~BitHandler(){
        delete seq;
    }

    void Append(int value) override{
        seq->Append(Bit<int>(value));
    }

    void Prepend(int value) override{
        seq->Prepend(Bit<int>(value));
    }

    void InsertAt(int value, size_t index) override{
        seq->InsertAt(Bit<int>(value), index);
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

    std::string Get(size_t index) override{
        return std::to_string(static_cast<bool>(seq->Get(index)));
    }

    json GetState() override{
        json json_state = json::array();
        for(size_t index = 0; index < seq->GetLength(); index++){
            if (static_cast<bool>(seq->Get(index))){
                json_state.push_back(1);
            }
            else{
                json_state.push_back(0);
            }
        }
        return json_state;
    }

    void Map() override{
    }

    void Where() override{
    }

    std::string Reduce() override{
        return "0";
    }

    std::string Subsequence(size_t start_index, size_t end_index) override{
        auto sub_sequence = seq->GetSubsequence(start_index, end_index);
        json json_state = json::array();
        for(size_t index = 0; index < sub_sequence->GetLength(); index++){
            if (static_cast<bool>(sub_sequence->Get(index))){
                json_state.push_back(1);
            }
            else{
                json_state.push_back(0);
            }
        }
        delete sub_sequence;
        return json_state.dump();
    }

    std::string BitNot() override{ 
        auto next_sequence = new BitSequence<int>(~(*seq)); 
        delete seq;
        seq = next_sequence; 
        return "Success"; 
    }

    std::string BitAnd(const std::string& mask_string) override{
        auto next_sequence = new BitSequence<int>((*seq) & create_mask(mask_string));
        delete seq;
        seq = next_sequence;
        return "Success";
    }

    std::string BitOr(const std::string& mask_string) override{
        auto next_sequence = new BitSequence<int>((*seq) | create_mask(mask_string));
        delete seq;
        seq = next_sequence;
        return "Success";
    }

    std::string BitXor(const std::string& mask_string) override{
        auto next_sequence = new BitSequence<int>((*seq) ^ create_mask(mask_string));
        delete seq;
        seq = next_sequence;
        return "Success";
    }
};

class AppController{
private:
    ISequenceHandler* array_model = nullptr;
    ISequenceHandler* list_model = nullptr;
    ISequenceHandler* bit_model = nullptr;

public:
    AppController(){
        array_model = new StandardHandler<ArraySequence<int>>();
        list_model = new StandardHandler<ListSequence<int>>();
        bit_model = new BitHandler();
    }

    ~AppController(){
        delete array_model;
        delete list_model;
        delete bit_model;
    }

    ISequenceHandler* GetModel(const std::string& name){
        if (name == "array"){
            return array_model;
        }
        if (name == "list"){
            return list_model;
        }
        if (name == "bit"){
            return bit_model;
        }
        
        throw std::invalid_argument("Unknown sequence type: " + name);
    }

    void ClearModel(const std::string& name){
        if (name == "array"){
            delete array_model;
            array_model = new StandardHandler<ArraySequence<int>>();
        } 
        else if (name == "list"){
            delete list_model;
            list_model = new StandardHandler<ListSequence<int>>();
        } 
        else if (name == "bit"){
            delete bit_model;
            bit_model = new BitHandler();
        }
    }
};

int main(){
    AppController controller;

    httplib::Server server;
    server.set_mount_point("/", "./interface_html");

    auto build_response = [](ISequenceHandler* handler, const std::string& log_message){
        json response_json;
        try{
            response_json["state"] = handler->GetState();
        } 
        catch (...){
            response_json["state"] = json::array();
        }
        response_json["log"] = log_message;
        return response_json.dump();
    };

    auto build_error_response = [](const std::string& log_message){
        json response_json;
        response_json["state"] = json::array();
        response_json["log"] = log_message;
        return response_json.dump();
    };

    server.Get("/api/get_state", [&](const httplib::Request& request, httplib::Response& response){
        try{
            std::string type = request.get_param_value("type");
            ISequenceHandler* handler = controller.GetModel(type);
            response.set_content(build_response(handler, "State"), "application/json");
        } 
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    server.Get("/api/clear", [&](const httplib::Request& request, httplib::Response& response){
        try{
            std::string type = request.get_param_value("type");
            controller.ClearModel(type);
            ISequenceHandler* handler = controller.GetModel(type);
            response.set_content(build_response(handler, "Cleared!"), "application/json");
        } 
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    auto handle_post_request = [&](const httplib::Request& request, httplib::Response& response, auto action_function){
        try{
            json request_json = json::parse(request.body);
            
            std::string type = "array";
            if (request_json.contains("type")){
                type = request_json["type"];
            }
            
            ISequenceHandler* handler = controller.GetModel(type);
            
            action_function(handler, request_json);
            response.set_content(build_response(handler, "Success"), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        } 
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Internal Error: ") + error.what()), "application/json");
        }
    };

    server.Post("/api/append", [&](const httplib::Request& request, httplib::Response& response){
        handle_post_request(request, response, [](ISequenceHandler* handler, json request_json){
            int value = 0;
            if (request_json.contains("val")){
                value = request_json["val"];
            }
            handler->Append(value);
        });
    });

    server.Post("/api/prepend", [&](const httplib::Request& request, httplib::Response& response){
        handle_post_request(request, response, [](ISequenceHandler* handler, json request_json){
            int value = 0;
            if (request_json.contains("val")){
                value = request_json["val"];
            }
            handler->Prepend(value);
        });
    });

    server.Post("/api/insert", [&](const httplib::Request& request, httplib::Response& response){
        handle_post_request(request, response, [](ISequenceHandler* handler, json request_json){
            int value = 0;
            if (request_json.contains("val")){
                value = request_json["val"];
            }
            
            int index = 0;
            if (request_json.contains("index")){
                index = request_json["index"];
            }
            
            handler->InsertAt(value, index);
        });
    });

    server.Post("/api/concat", [&](const httplib::Request& request, httplib::Response& response){
        handle_post_request(request, response, [](ISequenceHandler* handler, json request_json){
            if (request_json.contains("items")){
                handler->Concat(request_json["items"]);
            }
        });
    });

    server.Post("/api/map", [&](const httplib::Request& request, httplib::Response& response){
        handle_post_request(request, response, [](ISequenceHandler* handler, json request_json){
            handler->Map();
        });
    });

    server.Post("/api/where", [&](const httplib::Request& request, httplib::Response& response){
        handle_post_request(request, response, [](ISequenceHandler* handler, json request_json){
            handler->Where();
        });
    });

    server.Post("/api/get", [&](const httplib::Request& request, httplib::Response& response){
        try{
            json request_json = json::parse(request.body);
            
            std::string type = "array";
            if (request_json.contains("type")){
                type = request_json["type"];
            }
            
            ISequenceHandler* handler = controller.GetModel(type);
            
            int index = 0;
            if (request_json.contains("index")){
                index = request_json["index"];
            }
            
            response.set_content(build_response(handler, "Item: " + handler->Get(index)), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });
    
    server.Post("/api/get_first", [&](const httplib::Request& request, httplib::Response& response){
        try{
            json request_json = json::parse(request.body);
            
            std::string type = "array";
            if (request_json.contains("type")){
                type = request_json["type"];
            }
            
            ISequenceHandler* handler = controller.GetModel(type);
            
            response.set_content(build_response(handler, "First: " + handler->GetFirst()), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    server.Post("/api/get_last", [&](const httplib::Request& request, httplib::Response& response){
        try{
            json request_json = json::parse(request.body);
            
            std::string type = "array";
            if (request_json.contains("type")){
                type = request_json["type"];
            }
            
            ISequenceHandler* handler = controller.GetModel(type);
            
            response.set_content(build_response(handler, "Last: " + handler->GetLast()), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    server.Post("/api/reduce", [&](const httplib::Request& request, httplib::Response& response){
        try{
            json request_json = json::parse(request.body);
            
            std::string type = "array";
            if (request_json.contains("type")){
                type = request_json["type"];
            }
            
            ISequenceHandler* handler = controller.GetModel(type);
            
            response.set_content(build_response(handler, "Result: " + handler->Reduce()), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    server.Post("/api/subseq", [&](const httplib::Request& request, httplib::Response& response){
        try{
            json request_json = json::parse(request.body);
            
            std::string type = "array";
            if (request_json.contains("type")){
                type = request_json["type"];
            }
            
            ISequenceHandler* handler = controller.GetModel(type);
            
            int start_index = 0;
            if (request_json.contains("start")){
                start_index = request_json["start"];
            }
            
            int end_index = 0;
            if (request_json.contains("end")){
                end_index = request_json["end"];
            }

            response.set_content(build_response(handler, "Subseq: " + handler->Subsequence(start_index, end_index)), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    server.Post("/api/bit_not", [&](const httplib::Request& request, httplib::Response& response){
        try{
            ISequenceHandler* handler = controller.GetModel("bit");
            response.set_content(build_response(handler, handler->BitNot()), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    server.Post("/api/bit_and", [&](const httplib::Request& request, httplib::Response& response){
        try{
            json request_json = json::parse(request.body);
            
            std::string mask_string = "";
            if (request_json.contains("mask")){
                mask_string = request_json["mask"];
            }
            
            ISequenceHandler* handler = controller.GetModel("bit");
            
            response.set_content(build_response(handler, handler->BitAnd(mask_string)), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    server.Post("/api/bit_or", [&](const httplib::Request& request, httplib::Response& response){
        try{
            json request_json = json::parse(request.body);
            
            std::string mask_string = "";
            if (request_json.contains("mask")){
                mask_string = request_json["mask"];
            }
            
            ISequenceHandler* handler = controller.GetModel("bit");
            
            response.set_content(build_response(handler, handler->BitOr(mask_string)), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    server.Post("/api/bit_xor", [&](const httplib::Request& request, httplib::Response& response){
        try{
            json request_json = json::parse(request.body);
            
            std::string mask_string = "";
            if (request_json.contains("mask")){
                mask_string = request_json["mask"];
            }
            
            ISequenceHandler* handler = controller.GetModel("bit");
            
            response.set_content(build_response(handler, handler->BitXor(mask_string)), "application/json");
        } 
        catch (const Exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
        catch (const std::exception& error){
            response.set_content(build_error_response(std::string("Error: ") + error.what()), "application/json");
        }
    });

    std::cout << "\nhttp://localhost:8080\n";
    if (!server.listen("0.0.0.0", 8080)){
        std::cerr << "ОШИБКА: Не удалось запустить сервер! Порт 8080 занят.\n";
    }
    
    return 0;
}