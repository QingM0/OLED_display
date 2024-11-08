#include "combined.h"
SoftwareSerial mySerial(19, 18); // RX, TX

String serialValue;
String apiValue;
// 处理串口通信和服务器数据
void handleCommunicationAndData()
{
    // int iii = 0;
    // // 检查串口通信
    // if (mySerial.available())
    // {
    //     serialValue = mySerial.readString();

    // }

    fetchAPIData();
    // 如果串口数据存在且有效，则优先处理串口数据
    if (!serialValue.isEmpty())
    {
        processValues(serialValue); // 使用串口数据

        // sendDeleteRequest();     // API数据处理后发送DELETE请求
    }
    else if (!apiValue.isEmpty()) // 如果串口数据为空，处理API数据
    {
        processValues(apiValue); // 使用API数据
        // sendDeleteRequest();     // API数据处理后发送DELETE请求
    }

    // 清空串口和API数据，以便下一轮读取
    // sendDeleteRequest();
    // serialValue = "";
    // apiValue = ""; 
}

const char *data_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIFBTCCAu2gAwIBAgIQS6hSk/eaL6JzBkuoBI110DANBgkqhkiG9w0BAQsFADBP\n"
    "MQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJuZXQgU2VjdXJpdHkgUmVzZWFy\n"
    "Y2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBYMTAeFw0yNDAzMTMwMDAwMDBa\n"
    "Fw0yNzAzMTIyMzU5NTlaMDMxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBF\n"
    "bmNyeXB0MQwwCgYDVQQDEwNSMTAwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n"
    "AoIBAQDPV+XmxFQS7bRH/sknWHZGUCiMHT6I3wWd1bUYKb3dtVq/+vbOo76vACFL\n"
    "YlpaPAEvxVgD9on/jhFD68G14BQHlo9vH9fnuoE5CXVlt8KvGFs3Jijno/QHK20a\n"
    "/6tYvJWuQP/py1fEtVt/eA0YYbwX51TGu0mRzW4Y0YCF7qZlNrx06rxQTOr8IfM4\n"
    "FpOUurDTazgGzRYSespSdcitdrLCnF2YRVxvYXvGLe48E1KGAdlX5jgc3421H5KR\n"
    "mudKHMxFqHJV8LDmowfs/acbZp4/SItxhHFYyTr6717yW0QrPHTnj7JHwQdqzZq3\n"
    "DZb3EoEmUVQK7GH29/Xi8orIlQ2NAgMBAAGjgfgwgfUwDgYDVR0PAQH/BAQDAgGG\n"
    "MB0GA1UdJQQWMBQGCCsGAQUFBwMCBggrBgEFBQcDATASBgNVHRMBAf8ECDAGAQH/\n"
    "AgEAMB0GA1UdDgQWBBS7vMNHpeS8qcbDpHIMEI2iNeHI6DAfBgNVHSMEGDAWgBR5\n"
    "tFnme7bl5AFzgAiIyBpY9umbbjAyBggrBgEFBQcBAQQmMCQwIgYIKwYBBQUHMAKG\n"
    "Fmh0dHA6Ly94MS5pLmxlbmNyLm9yZy8wEwYDVR0gBAwwCjAIBgZngQwBAgEwJwYD\n"
    "VR0fBCAwHjAcoBqgGIYWaHR0cDovL3gxLmMubGVuY3Iub3JnLzANBgkqhkiG9w0B\n"
    "AQsFAAOCAgEAkrHnQTfreZ2B5s3iJeE6IOmQRJWjgVzPw139vaBw1bGWKCIL0vIo\n"
    "zwzn1OZDjCQiHcFCktEJr59L9MhwTyAWsVrdAfYf+B9haxQnsHKNY67u4s5Lzzfd\n"
    "u6PUzeetUK29v+PsPmI2cJkxp+iN3epi4hKu9ZzUPSwMqtCceb7qPVxEbpYxY1p9\n"
    "1n5PJKBLBX9eb9LU6l8zSxPWV7bK3lG4XaMJgnT9x3ies7msFtpKK5bDtotij/l0\n"
    "GaKeA97pb5uwD9KgWvaFXMIEt8jVTjLEvwRdvCn294GPDF08U8lAkIv7tghluaQh\n"
    "1QnlE4SEN4LOECj8dsIGJXpGUk3aU3KkJz9icKy+aUgA+2cP21uh6NcDIS3XyfaZ\n"
    "QjmDQ993ChII8SXWupQZVBiIpcWO4RqZk3lr7Bz5MUCwzDIA359e57SSq5CCkY0N\n"
    "4B6Vulk7LktfwrdGNVI5BsC9qqxSwSKgRJeZ9wygIaehbHFHFhcBaMDKpiZlBHyz\n"
    "rsnnlFXCb5s8HKn5LsUgGvB24L7sGNZP2CX7dhHov+YhD+jozLW2p9W4959Bz2Ei\n"
    "RmqDtmiXLnzqTpXbI+suyCsohKRg6Un0RC47+cpiVwHiXZAW+cn8eiNIjqbVgXLx\n"
    "KPpdzvvtTnOPlC7SQZSYmdunr3Bf9b77AiC/ZidstK36dRILKz7OA54=\n"
    "-----END CERTIFICATE-----\n";
// 获取服务器数据并存储在 apiValue 中
void fetchAPIData()
{
    HTTPClient http;
    http.begin("https://test.qingmo.moe/data", data_ca); // 开始连接

    int httpCode = http.GET(); // 发送GET请求

    if (httpCode > 0) // 如果请求成功
    {
        String payload = http.getString();
        Serial.println("服务器返回的数据: " + payload); // 输出获取到的数据

        // 解析JSON数组数据
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error)
        {
            JsonArray array = doc.as<JsonArray>(); // 将JSON解析为数组

            int valueFromServer = array[0]["number"]; // 获取数组中的number字段
            apiValue = String(valueFromServer);       // 将服务器的值保存为字符串
            Serial.print("API获取到的value: ");
            Serial.println(apiValue);
        }
        else
        {
            Serial.println("解析JSON时出错");
        }
    }
    else
    {
        Serial.print("HTTP请求失败，错误码: ");
        Serial.println(httpCode);
    }

    http.end(); // 结束HTTP连接
}

// 发送DELETE请求以清除API数据
void sendDeleteRequest()
{
    HTTPClient http;
    http.begin("https://test.qingmo.moe/clear"); // 连接清除端点
    http.addHeader("Content-Type", "application/json");
    int httpCodeDelete = http.sendRequest("DELETE");

    if (httpCodeDelete > 0)
    {
        Serial.println("服务器数据已清除");
    }
    else
    {
        Serial.println("清除服务器数据时出现错误");
    }

    http.end(); // 结束HTTP连接
}

// 根据串口或API的值执行操作
void processValues(String value)
{
    int ii = 0;
    if (value == "1")
    {
        UI_display_time();
        Serial.println("pm1.1");
        serialValue = "";
        apiValue = "";
        sendDeleteRequest();
    }
    else if (value == "2")
    {
        UI_display_weather();
        getHitokoto();
        sendDeleteRequest();
        serialValue = "";
        apiValue = "";
    }
    else if (value == "3")
    {
        robot_position();
        serialValue = "";
        apiValue = "";
        sendDeleteRequest();
    }
    else if (value == "4")
    {
        for (int i = 0; i < 3; i++)
        {
            robot_Forward();
        }

        sendDeleteRequest();
        serialValue = "";
        apiValue = "";
    }
    else if (value == "5")
    {
        for (int i = 0; i < 3; i++)
        {

            robot_Backward();
        }

        sendDeleteRequest();
        serialValue = "";
        apiValue = "";
    }
    if (ii < 2)
    {
        ii++;
    }
    else
    {
        sendDeleteRequest();
        serialValue = "";
        apiValue = "";
        ii = 0;
    }
    Serial.print("处理的value: ");
    Serial.println(value);
}