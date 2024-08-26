module com.example.lab11_2 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.lab11_2 to javafx.fxml;
    exports com.example.lab11_2;
}