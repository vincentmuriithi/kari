/*
 * Copyright (c) 2025 Vincent Muriithi Karimi
 *
 * Kari Library - An Arduino Library for Asynchronous and Sensor-Based Applications
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Vincent Muriithi Karimi
 * Library: Kari
 * License: Apache License 2.0
 */


#include "kariCells.h"


template <typename T, typename U>
kariTempSensor<T, U>::kariTempSensor(int signal): oneWire(signal), sensor(&oneWire){
    sensor.begin();
}

template <typename T, typename U>
kariTempSensor<T, U>& kariTempSensor<T, U>::measure(){
    sensor.requestTemperatures();
    return *this;
}


template <typename T, typename U>
kariTempSensor<T, U>& kariTempSensor<T, U>::onMeasureC(Callback callback){
    if (!callback) return *this;
    float temp_c= sensor.getTempCByIndex(0);
    callback(temp_c);
    return *this;
}



template <typename T, typename U>
kariTempSensor<T, U>& kariTempSensor<T, U>::onMeasureF(Callback callback){
    if (!callback) return *this;
    float temp_f= sensor.getTempFByIndex(0);
    callback(temp_f);
    return *this;
}


#if !defined(__AVR__)

template <typename T, typename U>
kariGSheetClient<T, U>::kariGSheetClient(T &gsheet, const char * client_email, 
const char * project_id, const char * private_key, const char * spreadsheet_id):
gsheet(gsheet), client_email(client_email), project_id(project_id), private_key(private_key), 
spreadsheet_id(spreadsheet_id) {}

template <typename T, typename U>
kariGSheetClient<T, U>& kariGSheetClient<T, U>::initialize(int refresh_rate, const char* dimension){
    gsheet.setPrerefreshSeconds(refresh_rate*60); // token refresh interval
    gsheet.begin(this->client_email, this->project_id, this->private_key);
    _status = gsheet.ready();
    this->valueRange.add("majorDimension", dimension);
    return *this;   
}

template <typename T, typename U>
kariGSheetClient<T, U>::operator bool() const{
    return _status;
}
template <typename T, typename U>
kariGSheetClient<T, U>& kariGSheetClient<T, U>::setHeadings(std::initializer_list<std::string> headings){
    bool ready = gsheet.ready();
    _status = ready;
    bool _isSent = false;
    int i = 0;
    if (ready && headings.size() > 0){
        while(!_isSent){
            for (auto data : headings){
            valueRange.set("values/[0]/[" + String(i) + "]", data);
            i++;
        }

        bool success = gsheet.values.update(&response, spreadsheet_id, "Sheet1!A1", &valueRange);
        _isSent = success ? true : false;
        valueRange.clear();
        }   
    }

    return *this;
}


template <typename T, typename U>
template <typename dataType>
kariGSheetClient<T, U>& kariGSheetClient<T, U>::attach(dataType data){
    bool ready = gsheet.ready();
    _status = ready;
    if (ready && data){
        valueRange.set("values/[" + String(_data) + "]/[" + String(elementCount) + "]", data);
        elementCount++;
    }

    return *this;
}

template <typename T, typename U>
kariGSheetClient<T, U>& kariGSheetClient<T, U>::transmit(){
    bool ready = gsheet.ready();
     _status = ready;
     
    if (ready)
    {   
        bool success =gsheet.values.append(&response, spreadsheet_id, "Sheet1!A1", &valueRange);

        if (success)
        {
            response.toString(response_data, true);
            valueRange.clear();
            _data++;
            this->_isSuccess = true;
        } 
        else{
            error_reason = gsheet.errorReason();
            this->_isSuccess = false;
        } // else for success
    } // if for ready

    elementCount = 0;
    return *this;
}

template <typename T, typename U>
kariGSheetClient<T, U>& kariGSheetClient<T, U>::onSuccess(Callback callback){
    if(!callback) return *this;
    if(_isSuccess)
        callback(response_data);

    return *this;
}

template <typename T, typename U>
kariGSheetClient<T, U>& kariGSheetClient<T, U>::onError(Callback callback){
    if(!callback) return *this;
    if(!_isSuccess)
        callback(error_reason);

    return *this;
}


#endif