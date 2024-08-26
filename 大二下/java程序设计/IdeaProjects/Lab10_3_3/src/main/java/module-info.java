module com.example.lab10_3_3 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.lab10_3_3 to javafx.fxml;
    exports com.example.lab10_3_3;
}