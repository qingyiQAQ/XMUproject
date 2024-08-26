module com.example.lab10_1 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.lab10_1 to javafx.fxml;
    exports com.example.lab10_1;
}