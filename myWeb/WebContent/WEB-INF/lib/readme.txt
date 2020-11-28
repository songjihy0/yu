JSTL使用需加入两个jar包:jstl与taglibs
<dependency>  
           <groupId>jstl</groupId>  
           <artifactId>jstl</artifactId>  
           <version>1.1.2</version>  
       </dependency>  
         
       <dependency>  
           <groupId>taglibs</groupId>  
           <artifactId>standard</artifactId>  
           <version>1.1.2</version>  
       </dependency>  


其次引入对应的taglib
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>  
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>  
<%@ taglib uri="http://java.sun.com/jsp/jstl/functions" prefix="fn"%>

