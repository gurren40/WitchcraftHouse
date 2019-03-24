package id.web.witchcraft.house;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.os.Build;

public class MyActivity extends QtActivity{
    private static MyActivity m_instance;

    public MyActivity()
    {
        m_instance = this;
    }
    
    public static String getDeviceModel()
    {
        return android.os.Build.MODEL;
    }
}
