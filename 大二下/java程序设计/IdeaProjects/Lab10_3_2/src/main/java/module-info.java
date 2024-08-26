module com.example.lab10_3_2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.web;



    opens com.example.lab10_3_2 to javafx.fxml;
    exports com.example.lab10_3_2;
}