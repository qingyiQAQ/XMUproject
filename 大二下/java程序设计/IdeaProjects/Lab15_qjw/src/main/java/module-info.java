module com.example.lab15_qjw {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens com.example.lab15_qjw to javafx.fxml;
    exports com.example.lab15_qjw;
}