package org.example;

import org.eclipse.paho.client.mqttv3.*;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

import java.util.Random;

public class SensorDataPublisher {

    private static final String BROKER = "tcp://localhost:1883";
    private static final String CLIENT_ID = "SensorDataPublisher";
    private static final String TOPIC = "sensor/data";

    private static final Random random = new Random();

    public static void main(String[] args) {
        MqttClient client;
        try {
            client = new MqttClient(BROKER, CLIENT_ID, new MemoryPersistence());
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            System.out.println("Connecting to broker: " + BROKER);
            client.connect(connOpts);
            System.out.println("Connected");

            while (true) {
                double temperature = generateTemperature();
                double humidity = generateHumidity();
                double light = generateLight();
                double airQuality = generateAirQuality();

                String sensorData = "T" + temperature + "H" + humidity +
                        "L" + light + "A" + airQuality;

                // Publish sensor data to MQTT broker
                MqttMessage message = new MqttMessage(sensorData.getBytes());
                client.publish(TOPIC, message);
                System.out.println("Message published: " + sensorData);

                // Sleep for a while before publishing next data
                Thread.sleep(5000); // Adjust interval as needed
            }
        } catch (MqttException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static double generateTemperature() {
        // Simulate temperature data generation
        return 20 + random.nextGaussian(); // Mean: 20°C, Standard Deviation: 1°C
    }

    private static double generateHumidity() {
        // Simulate humidity data generation
        return 50 + random.nextGaussian(); // Mean: 50%, Standard Deviation: 5%
    }

    private static double generateLight() {
        // Simulate light data generation
        return 500 + random.nextGaussian() * 100; // Mean: 500 lux, Standard Deviation: 100 lux
    }

    private static double generateAirQuality() {
        // Simulate air quality data generation
        return 100 + random.nextGaussian() * 10; // Mean: 100, Standard Deviation: 10
    }
}
