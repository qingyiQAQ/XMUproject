package com.example.server;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.ArrayList;

@Mapper
public interface SensorMapper {

    @Insert("insert into sensormessage(datetime,temperature,humidity,light,airQuality) values (#{dateTime},#{temperature},#{humidity},#{light},#{airQuality})")
    void insertSensorData(SensorMessage sensorMessage);

    @Select("select * from sensormessage")
    ArrayList<SensorMessage> getAllSensorData();
}
