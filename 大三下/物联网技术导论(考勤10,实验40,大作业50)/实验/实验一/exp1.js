/** 说明：MQTT 方式对接数据
 *  备注：MQTT是一个轻量级协议，使用MQTT协议的中心是broker（服务器/代理），客户端通过订阅消息和
 *       发布消息进行数据交互。使用MQTT方式的步骤如下：
 *           1.直接连接MQTT服务器（本示例使用的是ActiveMQ消息中间件）
 *           2.引用第三方库 mqtt.js，版本是3.0.0，使用手册详见 https://github.com/mqttjs/MQTT.js
 *           3.数据对接
 *  功能：通过MQTT方式读取数据并将数据挂接到物体（app.query('car01')[0]01）身上，当温度>30℃时，app.query('car01')[0]01变红
 *  难度：★★☆☆☆
 **/

// 加载场景代码 
var app = new THING.App({
    url: 'https://www.thingjs.com/static/models/factory',  // 场景地址
    background: '#000000',
    env: 'Seaside',
});

// 引入样式文件
THING.Utils.dynamicLoad([
    'https://www.thingjs.com/static/lib/mqtt.min.js',
    '/guide/examples/css/measure/panel.css'
], function () {
    app.on('load', function () {
        // 物体身上创建monitorData对象 用于存储动态监控数据
        app.query('car03')[0].monitorData = {
            '温度': ''
        };
        var mq_publiser = new MQTT_publisher();
        var mq_subscriber = new MQTT_subscriber(); // 创建mq服务类

        new THING.widget.Button('开启读取', function () {
            mq_subscriber.initConnection();
            mq_publiser.initConnection();

            // 摄像机飞行到某位置
            app.camera.flyTo({
                position: [50.00333914719489, 21.747771367094018, 35.16550370725474],
                target: [12.071590067214768, 1.9553381388502726, -5.857819062456373],
                time: 1000,
            });
        });

        new THING.widget.Button('关闭读取', function () {
            mq_subscriber.disconnection();
            mq_publiser.disconnection();

            // 摄像机飞行到某位置
            app.camera.flyTo({
                position: [36.013, 42.67799999999998, 61.72399999999999],
                target: [1.646, 7.891, 4.445],
                time: 1000,
            });
        });

        // 创建html
        createHtml();
        initThingJsTip("MQTT 是一个轻量级协议，使用 MQTT 协议的中心是 broker（服务器/代理），客户端通过订阅消息和发布消息进行数据交互。<br>点击【开启读取】进行数据读取，读取到的数据将在数据详情面板进行显示，点击【关闭读取】停止数据读取！");
    })
})

/** 连接MQ服务
 *  说明：
 *      1.测试使用的MQTT服务器为 ActiveMQ（版本为5.16.2）。
 *      2.设备端每隔4秒会向服务器 /topic/monitor/temperature/one 主题发送一条温度数据。
 *      3.客户端订阅了 /topic/monitor/temperature/one 主题。
 *      4.可以通过其他MQTT客户端向服务器 /topic/monitor/temperature/one 主题发送消息，
 *        验证MQTT服务
 **/
class MQTT_subscriber {
    // 构造器
    constructor() {
        this.init();
    }
    // 初始化
    init() {
        // 数据推送的url，可修改为自己的服务地址
        this.socketUrl = 'wss://www.3dmmd.cn:8086';
        this.options = {
            clienId: 'mqtt_' + Math.random().toString(16).substr(2, 8)  // 客户端标识id
        }
        // 连接
        this.mqttClient = null;
    }
    // 初始化连接
    initConnection() {
        var _this = this;
        this.mqttClient = mqtt.connect(this.socketUrl, this.options);
        this.mqttClient.on('connect', function () {
            console.log("连接成功");
            // 订阅主题
            _this.mqttClient.subscribe('/mqtt/WebOfThings/test', function (err) {
                if (!err) {
                    console.log("订阅成功");
                }
            });
        });

        // 处理接收到的消息
        this.mqttClient.on('message', function (topic, message) {
            // message 是 Buffer
            const data = message.toString();
            console.log(`接收到数据：${data}`);
            updateState(data); // 更新状态
        });
    }

    // 连接成功后的回调，订阅主题：/mqtt/WebOfThings/test
    successCallback(data) {


    }
    // 关闭连接
    disconnection() {
        if (this.mqttClient) {
            this.mqttClient.end();
            this.mqttClient = null;
            console.log('MQTT连接已关闭！');
        }
    }
}

class MQTT_publisher {
    //构造器
    constructor() {
        this.init();
    }
    //初始化
    init() {
        this.socketUrl = 'wss://www.3dmmd.cn:8086';
        this.options = {
            clienId: 'mqtt_' + Math.random().toString(16).substr(2, 8)  // 客户端标识id
        }
    }
    //初始化连接
    initConnection() {
        var _this = this;
        if (_this.mqttClient != null) return;
        _this.mqttClient = mqtt.connect(_this.socketUrl);
        _this.mqttClient.on('connect', function () {
            setInterval(() => {
                _this.mqttClient.publish('/mqtt/WebOfThings/test', Math.floor(Math.random() * 40).toString())
            }, 1000)
            // console.log("连接成功");
            // _this.successCallback();
        })
        _this.mqttClient.on('error', function (error) {
            console.log("连接失败");
            console.log(error);
        })
    }

    //连接成功后每隔1s发布一个温度数据
    successCallback(data) {
        var _this = this;
        _this.mqttClient.publish('/mqtt/WebOfThings/test', Math.floor(Math.random() * 40).toString());

    }
    // 关闭连接
    disconnection() {
        console.log('连接已关闭！');
        this.mqttClient.end();
        this.mqttClient = null;
    }
}


// 接收推送数据后更新状态
function updateState(data) {
    app.query('car03')[0].setAttribute("monitorData/温度", data);
    nowDatetime();
    if (($('.empty').length)) {
        $('.empty').remove();
    }
    if (!($('.tj-group').length)) {
        let tbody = `<tbody class="tj-group" id="tb-line"></tbody>`;
        $('.tj-table').prepend(tbody);
    }
    let tr =
        `<tr class="tj-group-content">
             <td class="tj-key">` + dateString + `</td>
             <td class="tj-value">` + data + `℃</td>
         </tr>`;
    $('.tj-group').prepend(tr);
    changeColor(app.query('car03')[0]);
}

// 获取系统日期
function nowDatetime() {
    var date = new Date();
    var hours = (date.getHours()) > 9 ? (date.getHours()) : "0" + (date.getHours());
    var minutes = (date.getMinutes()) > 9 ? (date.getMinutes()) : "0" + (date.getMinutes());
    var seconds = (date.getSeconds()) > 9 ? (date.getSeconds()) : "0" + (date.getSeconds());
    dateString =
        hours + ":" +
        minutes + ":" +
        seconds;
    return dateString;
}

// 根据不同的温度系数对车辆的颜色进行控制
function changeColor(obj) {
    var temper = obj.getAttribute("monitorData/温度");
    var value = parseInt(temper);
    console.log(value);

    if (value >= 0 && value <= 10) {
        // 当温度在0~10°C时，变红
        obj.style.color = 'rgb(255,0,0)';
    } else if (value > 10 && value <= 20) {
        // 当温度在10~20°C时，变绿
        obj.style.color = 'rgb(0,255,0)';
    } else if (value > 20 && value <= 30) {
        // 当温度在20~30°C时，变蓝
        obj.style.color = 'rgb(0,0,255)';
    } else {
        // 其他情况恢复默认颜色
        obj.style.color = null;
    }
}

// 创建html界面
function createHtml() {
    // 数据详情界面
    let dataDetails =
        `<div id="dataDetails" class="tj-panel property-panel tj-has-title tj-sizable tj-property-panel tj-pinned" style="position: absolute; right: 10px; top: 220px; width: 315px; height: 416px; transform: none;">
                 <div class="tj-close"></div>
                 <div class="tj-title" style="cursor: move; user-select: none;">数据详情</div>
                 <div class="tj-panel-body" style="padding-top: 0px;">
                     <div class="tj-panel-container tj-scroll-bar">
                         <table class="tj-table">
                             <div class="empty">暂无数据</div>
                         </table>
                     </div>
                 </div>
             </div>`;
    $('#div2d').append(dataDetails);
    // 点击按钮关闭面板
    $('#dataDetails .tj-close').on('click', function () {
        $('#dataDetails').css('display', 'none');
    });
}