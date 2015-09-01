<?php

class StrikeIron {

  private $_key = '';

  private $_password = '';

  public $wsdl = 'http://ws.strikeiron.com/PhoneValidation3?WSDL';

  public $url = 'http://ws.strikeiron.com';

  private function __construct($key, $password) {
    $this->_key = $key;
    $this->_password = $password;

    $client = new SoapClient($this->$wsdl, array('trace' => 1, 'exceptions' => 1));
    //create user array for SOAP header
    $user = array(
      "RegisteredUser" => array(
        'UserID'   => $this->_key,
        'Password' => $this->_password
      )
    );
    $header = new SoapHeader('http://ws.strikeiron.com', 'LicenseInfo', $user);

    // set soap headers - this will apply to all operations
    $client->__setSoapHeaders($header);
  }
  /**
   * @param $phone
   */
  public function getPhone($phone = NULL) {

    try
    {
      //Calls ValidateNumber and displays the result
      $this->ValidateNumber($phone);
    }
    catch (Exception $e)
    {
      echo $e->getMessage() . "<br />";
    }
  }

  /**
   * @param $email
   */
  public function getEmail($email = NULL) {

    try
    {
      //Calls ValidateEmail and displays the result
      $this->ValidateEmail($email);
    }
    catch (Exception $e)
    {
      echo $e->getMessage() . "<br />";
    }
  }

  /**
   * @param $phone
   */
  private function ValidateNumber($phone) {
    global $client;

    //Set up parameters for ValidateNumber
    $phoneNumber = !empty($phone) ? $phone : '9194674545';

    //Set up parameter array
    $params = array("PhoneNumber" => $phoneNumber);

    //call web service operation
    $result = $client->__soapCall("ValidateNumber", array($params), NULL, NULL, $output_header);

    return $result;
  }


  /**
   * @param $phone
   */
  private function ValidateEmail($email) {
    global $client;

    //Set up input parameters for the VerifyEmail operation
    $email_address = !empty($email) ? $email : 'test.bot@testtronica.com';
    $timeout = '30';

    //set up parameter array
    $params = array(
      "Email"   => $email_address,
      "Timeout" => $timeout,
    );

    //call the web service operation
    $result = $client->__soapCall("VerifyEmail", array($params), null, null, $output_header);

    return $result;
  }


  /**
   * @return string
   */
  public function getKey() {
    return $this->key;
  }

  /**
   * @param string $key
   */
  public function setKey($key) {
    $this->key = $key;
  }

  /**
   * @return string
   */
  public function getPassword() {
    return $this->password;
  }

  /**
   * @param string $password
   */
  public function setPassword($password) {
    $this->password = $password;
  }

  /**
   * @return string
   */
  public function getWsdl() {
    return $this->wsdl;
  }

  /**
   * @param string $wsdl
   */
  public function setWsdl($wsdl) {
    $this->wsdl = $wsdl;
  }

  /**
   * @return string
   */
  public function getUrl() {
    return $this->url;
  }

  /**
   * @param string $url
   */
  public function setUrl($url) {
    $this->url = $url;
  }


}

?>