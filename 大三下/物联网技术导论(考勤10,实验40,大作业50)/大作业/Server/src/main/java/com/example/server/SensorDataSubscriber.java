package com.example.server;

import org.eclipse.paho.client.mqttv3.*;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.springframework.context.ApplicationContext;

import java.time.LocalDateTime;

public class SensorDataSubscriber implements MqttCallback {

    public ApplicationContext context;
    private SensorMapper sensorMapper;

    private static final String BROKER = "tcp://localhost:1883";
    private static final String CLIENT_ID = "SensorDataSubscriber";
    private static final String TOPIC = "sensor/data";

    public SensorDataSubscriber(ApplicationContext context) {
        this.context = context;
    }

    public void subscribe() {
        try {
            MqttClient client = new MqttClient(BROKER, CLIENT_ID, new MemoryPersistence());
            client.setCallback(this);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            System.out.println("Connecting to broker: " + BROKER);
            client.connect(connOpts);
            System.out.println("Connected");
            client.subscribe(TOPIC);
            System.out.println("Subscribed to topic: " + TOPIC);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void connectionLost(Throwable cause) {
        System.out.println("Connection lost: " + cause.getMessage());
    }

    @Override
    public void messageArrived(String topic, MqttMessage message) throws Exception {
        System.out.println("Message received on topic " + topic + ": " + new String(message.getPayload()));
        String[] dataParts = new String(message.getPayload()).split("[THLA]");
        double temperature = Double.parseDouble(dataParts[1]);
        double humidity = Double.parseDouble(dataParts[2]);
        double light = Double.parseDouble(dataParts[3]);
        double airQuality = Double.parseDouble(dataParts[4]);
        LocalDateTime localDateTime = LocalDateTime.now();
        sensorMapper = context.getBean(SensorMapper.class);
        sensorMapper.insertSensorData(new SensorMessage(localDateTime, temperature, humidity, light, airQuality));
        System.out.println("???");
    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken token) {
    }
}
