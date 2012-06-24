INSTALL
=======
1. Checkout the latest dev version of Views 3.x
2. Enable Views 3.x and YQL Views Query

HELP
====
1. Tutorial on how to use this module is available in the Advanced Help page.
2. More reference on YQL can be found in http://developer.yahoo.com/yql/guide/
3. YQL Console is a very useful tool when working with YQL. It can be found in http://developer.yahoo.com/yql/console/

PERFORMANCE
===========
1. Be careful of "Query Settings: Number of items". This amount of items will be fetched on every page of the view. For example, if you have 10 items per page and "Number of items = 100", 100 items will be fetched regardless which page you are executing.