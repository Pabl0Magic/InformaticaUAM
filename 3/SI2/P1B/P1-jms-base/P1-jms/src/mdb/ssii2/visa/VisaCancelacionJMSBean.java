/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * VisaCancelacionJMSBean.java
 */

package ssii2.visa;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ejb.EJBException;
import javax.ejb.MessageDriven;
import javax.ejb.MessageDrivenContext;
import javax.ejb.ActivationConfigProperty;
import javax.jms.MessageListener;
import javax.jms.Message;
import javax.jms.TextMessage;
import javax.jms.JMSException;
import javax.annotation.Resource;
import java.util.logging.Logger;

/**
 * @author jaime
 */
@MessageDriven(mappedName = "jms/VisaPagosQueue")
public class VisaCancelacionJMSBean extends DBTester implements MessageListener {
    static final Logger logger = Logger.getLogger("VisaCancelacionJMSBean");
    @Resource
    private MessageDrivenContext mdc;

    private static final String SELECT_COD_RESPUESTA =
                                    "select codRespuesta from pago "+
                                    "where idAutorizacion=?";
                                    
    private static final String UPDATE_CANCELA_QRY = 
                                    "update pago " +
                                    "set codRespuesta=999 "+
                                    "where idautorizacion=?";

    private static final String UPDATE_SALDO_QRY = 
                                    "update tarjeta "+
                                    "set saldo=saldo +"+
                                    "(select importe from pago "+
                                    "where idAutorizacion=?) "+
                                    "where numeroTarjeta="+
                                    "(select numeroTarjeta from pago "+
                                    "where idAutorizacion=?) ";
    

    public VisaCancelacionJMSBean() {
    }

    // TODO : Método onMessage de ejemplo
    // Modificarlo para ejecutar el UPDATE definido más arriba,
    // asignando el idAutorizacion a lo recibido por el mensaje
    // Para ello conecte a la BD, prepareStatement() y ejecute correctamente
    // la actualización
    public void onMessage(Message inMessage) {
        TextMessage msg = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        boolean ret = false;
        String str="";
        Connection con = null;

        try {
            if (inMessage instanceof TextMessage) {
                msg = (TextMessage) inMessage;
                logger.info("MESSAGE BEAN: Message received: " + msg.getText());

                con = getConnection();



                /* Obtener el codigo desde el mensaje */
                int idAutorizacion = Integer.parseInt(msg.getText());

                /* Comprobar codigo respuesta */
                String codRespuestaStr = SELECT_COD_RESPUESTA;
                logger.info(codRespuestaStr);
                pstmt = con.prepareStatement(codRespuestaStr);
                pstmt.setInt(1, idAutorizacion);
                rs = pstmt.executeQuery();
                if(rs.next()){
                    /* Comprobamos que elcodigo de respuesta es 000 */
                    String codRespuesta = rs.getString("codRespuesta");
                    
                    if(codRespuesta == "000"){
                        String cancela = UPDATE_CANCELA_QRY;
                        logger.info(cancela);
                        pstmt = con.prepareStatement(cancela);
                        pstmt.setInt(1, idAutorizacion);
                        
                        ret = false;
                        if (!pstmt.execute() && pstmt.getUpdateCount() == 1) {
                            ret = true;
                        } else{
                            str="Error cancelando pago.";
                        }

                        if (ret == true) {
                            String updateSaldo = UPDATE_SALDO_QRY;
                            logger.info(updateSaldo);
                            pstmt = con.prepareStatement(updateSaldo);
                            pstmt.setInt(1, idAutorizacion);
                            pstmt.setInt(2, idAutorizacion);

                            ret = false;
                            if (!pstmt.execute() && pstmt.getUpdateCount() == 1) {
                                ret = true;
                            } else{
                                str="Error devolviendo dinero.";
                            }
                        }    
                    } else{
                        ret=false;
                        str="Este pago no se puede cancelar.";
                    }

                }else{
                    ret = false;
                    str="Pago no encontrado.";
                }
                    
                if(!ret){
                    logger.warning("ERROR: Error borrando pago. "+str);
                }


            } else {
                logger.warning(
                        "Message of wrong type: "
                        + inMessage.getClass().getName());
            }
        } catch (JMSException e) {
            e.printStackTrace();
            mdc.setRollbackOnly();
        } catch (Throwable te) {
            te.printStackTrace();
        } finally {
            try {
                if (rs != null) {
                    rs.close(); 
                    rs = null;
                }
                if (pstmt != null) {
                    pstmt.close(); 
                    pstmt = null;
                }
                if (con != null) {
                    closeConnection(con); 
                    con = null;
                }
            } catch (SQLException e) {

            }
        }
    }

}
