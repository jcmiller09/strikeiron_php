<?php

class StrikeIron {

  public $_url = 'http://ws.strikeiron.com';
  private $_key;
  private $_password;
  private $client = '';

  public function __construct($key, $password) {
    $this->_key = $key;
    $this->_password = $password;

    $this->client = new SoapClient('http://ws.strikeiron.com/emv6Hygiene?WSDL', array(
      'trace' => 1,
      'exceptions' => 1
    ));
    //create user array for SOAP header
    $user = array(
      "RegisteredUser" => array(
        'UserID' => $this->_key,
        'Password' => $this->_password
      )
    );
    $header = new SoapHeader($this->_url, 'LicenseInfo', $user);

    // set soap headers - this will apply to all operations
    $this->client->__setSoapHeaders($header);
  }

  /**
   * @param $phone
   * @return object @result
   */
  public function getPhone($phone = NULL) {

    try {
      //Calls ValidateNumber and displays the result
      $result = $this->ValidateNumber($phone);
    } catch (Exception $e) {
      echo $e->getMessage() . "<br />";
    }
    if (!empty($result)) {
      return $result;
    }
    return FALSE;
  }

  /**
   * @param $phone
   * @return object $result
   */
  private function ValidateNumber($phone) {
    $this->client->__setLocation('http://ws.strikeiron.com/PhoneValidation3?WSDL');

    //Set up parameters for ValidateNumber
    $phoneNumber = !empty($phone) ? $phone : '9194674545';

    //Set up parameter array
    $params = array("PhoneNumber" => $phoneNumber);

    //call web service operation
    $result = $this->client->__soapCall("ValidateNumber", array($params), NULL, NULL, $output_header);

    return $result;
  }

  /**
   * @param $email
   * @return object $result
   */
  public function getEmail($email = NULL) {
    try {
      //Calls ValidateEmail and displays the result
      $result = StrikeIron::ValidateEmail($email);
    } catch (Exception $e) {
      echo $e->getMessage() . "<br />";
    }
    if (!empty($result)) {
      return $result;
    }
    return FALSE;
  }

  /**
   * @param $email
   * @return object $result

   */
  private function ValidateEmail($email) {
    $this->client->__setLocation('http://ws.strikeiron.com/emv6Hygiene?WSDL');
    //Set up input parameters for the VerifyEmail operation
    $email_address = !empty($email) ? $email : 'test.bot@testtronica.com';
    $timeout = '30';

    //set up parameter array
    $params = array(
      "Email" => $email_address,
      "Timeout" => $timeout,
    );

    //call the web service operation
    $result = $this->client->__soapCall("VerifyEmail", array($params), NULL, NULL, $output_header);
    //add some super basic semantic results data
    $result->valid = $result->VerifyEmailResult->ServiceStatus->StatusNbr == 200 ? TRUE : FALSE;
    if (!empty($result->VerifyEmailResult->ServiceResult->Reason->Description)) {
      $result->reason = $result->VerifyEmailResult->ServiceResult->Reason->Description;
    }
    $result->hygiene = $result->VerifyEmailResult->ServiceResult->HygieneResult;
    $result->remaining_hits = $output_header['SubscriptionInfo']->RemainingHits;
    return $result;
  }

  /**
   * @return string
   */
  public function getKey() {
    return $this->_key;
  }

  /**
   * @param string $key
   */
  public function setKey($key) {
    $this->_key = $key;
  }

  /**
   * @return string
   */
  public function getPassword() {
    return $this->_password;
  }

  /**
   * @param string $password
   */
  public function setPassword($password) {
    $this->_password = $password;
  }

  /**
   * @return string
   */
  public function getUrl() {
    return $this->_url;
  }

  /**
   * @param string $url
   */
  public function setUrl($url) {
    $this->_url = $url;
  }
}

