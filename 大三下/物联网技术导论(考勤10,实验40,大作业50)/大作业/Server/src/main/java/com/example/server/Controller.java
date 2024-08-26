package com.example.server;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;

@RestController
public class Controller {

    @Autowired
    private SensorMapper sensorMapper;

    @GetMapping("/sensorData")
    public ArrayList<SensorMessage> getAllSensorData(){return sensorMapper.getAllSensorData();}
}
