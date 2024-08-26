package com.example.server;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@AllArgsConstructor
public class SensorMessage {
    private LocalDateTime dateTime;
    private double temperature;
    private double humidity;
    private double light;
    private double airQuality;
}
