package id.web.witchcraft.house;
import org.qtproject.qt5.android.bindings.QtActivity;

public class MyActivity extends QtActivity{
    private static MyActivity m_instance;

    public MyActivity()
    {
        m_instance = this;
    }
}
