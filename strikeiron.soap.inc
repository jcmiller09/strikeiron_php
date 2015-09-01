<?php

class StrikeIron {

  public $key = 'my user key / id';

  public $password = 'my password';

  public $wsdl = 'http://ws.strikeiron.com/PhoneValidation3?WSDL';

  public $url = 'http://ws.strikeiron.com';

  private function __construct() {
    $client = new SoapClient($this->$wsdl, array('trace' => 1, 'exceptions' => 1));
    //create user array for SOAP header
    $user = array(
      "RegisteredUser" => array(
        'UserID' => $this->key,
        'Password' => $this->password
      )
    );
    $header = new SoapHeader('http://ws.strikeiron.com', 'LicenseInfo', $user);

    // set soap headers - this will apply to all operations
    $client->__setSoapHeaders($header);
  }
  /**
   * @param $email
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
   *
   */
  private function ValidateNumber($phone) {
    global $client;

    //Set up parameters for ValidateNumber
    $phoneNumber = !empty($phone) ? $phone : '9194674545';

    //Set up parameter array
    $params = array("PhoneNumber" => $phoneNumber);

    //call web service operation
    $result = $client->__soapCall("ValidateNumber", array($params), NULL, NULL, $output_header);

    //show service output
    //note that this are only some of the fields returned by the service
    echo '<h1>ValidateNumber Result</h1><br>';
    output_Result($result->ValidateNumberResult->ServiceResult);

    //show status info
    echo '<br><h2>Status Info</h2><br>';
    output_status_info($result->ValidateNumberResult->ServiceStatus);

    //show subscription info
    echo '<br><h2>Subscription Info</h2><br>';
    output_subscription_info($output_header['SubscriptionInfo']);
  }

  public function output_Result($svcResult) {
    echo '<table border="1">';
    echo '<tr><td>State</td><td>' . $svcResult->State . '</td></tr>';
    echo '<tr><td><b>City</b></td><td><b>' . $svcResult->City . '</b></td></tr>';
    echo '<tr><td><b>County</b></td><td><b>' . $svcResult->County . '</b></td></tr>';
    echo '<tr><td><b>Timezone</b></td><td><b>' . $svcResult->Timezone . '</b></td></tr>';
    echo '</table><br>';
  }

  public function output_status_info($svcStatus) {
    echo '<table border="1">';
    echo '<tr><td>StatusNbr</td><td>' . $svcStatus->StatusNbr . '</td></tr>';
    echo '<tr><td>StatusDescription</td><td>' . $svcStatus->StatusDescription . '</td></tr>';
    echo '</table><br>';
  }

  public function output_subscription_info($subInfo) {
    echo '<table border="1">';
    echo '<tr><td>License Status</td><td>' . $subInfo->LicenseStatus . '</td></tr>';
    echo '<tr><td>License Action</td><td>' . $subInfo->LicenseAction . '</td></tr>';
    echo '<tr><td>Remaining Hits</td><td>' . $subInfo->RemainingHits . '</td></tr>';
    echo '</table>';
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
