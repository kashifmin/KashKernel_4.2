


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>Bindass-Boost-a110-JB-Kernel-mt6577/kernel/block/bfq.h at JB · bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <link rel="logo" type="image/svg" href="https://github-media-downloads.s3.amazonaws.com/github-logo.svg" />
    <meta property="og:image" content="https://github.global.ssl.fastly.net/images/modules/logos_page/Octocat.png">
    <meta name="hostname" content="github-fe126-cp1-prd.iad.github.net">
    <meta name="ruby" content="ruby 1.9.3p194-tcs-github-tcmalloc (a846054d10) [x86_64-linux]">
    <link rel="assets" href="https://github.global.ssl.fastly.net/">
    <link rel="conduit-xhr" href="https://ghconduit.com:25035/">
    <link rel="xhr-socket" href="/_sockets" />
    


    <meta name="msapplication-TileImage" content="/windows-tile.png" />
    <meta name="msapplication-TileColor" content="#ffffff" />
    <meta name="selected-link" value="repo_source" data-pjax-transient />
    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="collector-cdn.github.com" name="octolytics-script-host" /><meta content="github" name="octolytics-app-id" /><meta content="75DD6C88:06F3:4977E17:52CABC0F" name="octolytics-dimension-request_id" /><meta content="6142664" name="octolytics-actor-id" /><meta content="kashifmin" name="octolytics-actor-login" /><meta content="f6cfe5077c4d146c292c7325f856e3d3ed63b720f463c305ee2f87ee3eb7199e" name="octolytics-actor-hash" />
    

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="XybXrS3BehyiAYe/MJAntwUExUhHELY12Qjxtz2sQk4=" name="csrf-token" />

    <link href="https://github.global.ssl.fastly.net/assets/github-3944f96c1c19f752fe766b332fb7716555c8296e.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://github.global.ssl.fastly.net/assets/github2-26223e212ca99f1bf10e8a9619bc7a09400ed4f6.css" media="all" rel="stylesheet" type="text/css" />
    

    

      <script src="https://github.global.ssl.fastly.net/assets/frameworks-29a3fb0547e33bd8d4530bbad9bae3ef00d83293.js" type="text/javascript"></script>
      <script src="https://github.global.ssl.fastly.net/assets/github-4ac46f893910c3da1bdbe9b20092fe75867245d8.js" type="text/javascript"></script>
      
      <meta http-equiv="x-pjax-version" content="8131df651c3e5051e69641ddd10fc78c">

        <link data-pjax-transient rel='permalink' href='/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/blob/a8505c96c322d6fc1d1f40ea02c987e280f58e64/kernel/block/bfq.h'>
  <meta property="og:title" content="Bindass-Boost-a110-JB-Kernel-mt6577"/>
  <meta property="og:type" content="githubog:gitrepository"/>
  <meta property="og:url" content="https://github.com/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577"/>
  <meta property="og:image" content="https://github.global.ssl.fastly.net/images/gravatars/gravatar-user-420.png"/>
  <meta property="og:site_name" content="GitHub"/>
  <meta property="og:description" content="Bindass-Boost-a110-JB-Kernel-mt6577 - BindassBoost a110 JB Kernel (MT6577)"/>

  <meta name="description" content="Bindass-Boost-a110-JB-Kernel-mt6577 - BindassBoost a110 JB Kernel (MT6577)" />

  <meta content="5082656" name="octolytics-dimension-user_id" /><meta content="bindassdost" name="octolytics-dimension-user_login" /><meta content="12839156" name="octolytics-dimension-repository_id" /><meta content="bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="true" name="octolytics-dimension-repository_is_fork" /><meta content="7984720" name="octolytics-dimension-repository_parent_id" /><meta content="wiko-sources/cink-king" name="octolytics-dimension-repository_parent_nwo" /><meta content="7984720" name="octolytics-dimension-repository_network_root_id" /><meta content="wiko-sources/cink-king" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/commits/JB.atom" rel="alternate" title="Recent Commits to Bindass-Boost-a110-JB-Kernel-mt6577:JB" type="application/atom+xml" />

  </head>


  <body class="logged_in  env-production linux vis-public fork page-blob">
    <div class="wrapper">
      
      
      
      


      <div class="header header-logged-in true">
  <div class="container clearfix">

    <a class="header-logo-invertocat" href="https://github.com/">
  <span class="mega-octicon octicon-mark-github"></span>
</a>

    
    <a href="/notifications" class="notification-indicator tooltipped downwards" data-gotokey="n" title="You have no unread notifications">
        <span class="mail-status all-read"></span>
</a>

      <div class="command-bar js-command-bar  in-repository">
          <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">

<input type="text" data-hotkey=" s" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
    data-username="kashifmin"
      data-repo="bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577"
      data-branch="JB"
      data-sha="9d3779b7eec8a264b099f472f7d5835141476e55"
  >

    <input type="hidden" name="nwo" value="bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577" />

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item js-this-repository-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked" />
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item js-all-repositories-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global" />
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="octicon help tooltipped downwards" title="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

</form>
        <ul class="top-nav">
          <li class="explore"><a href="/explore">Explore</a></li>
            <li><a href="https://gist.github.com">Gist</a></li>
            <li><a href="/blog">Blog</a></li>
          <li><a href="https://help.github.com">Help</a></li>
        </ul>
      </div>

    


  <ul id="user-links">
    <li>
      <a href="/kashifmin" class="name">
        <img height="20" src="https://1.gravatar.com/avatar/e87369eacb242110c6623b83856fb05d?d=https%3A%2F%2Fidenticons.github.com%2F8161df31293150ccb0ebad3b88315ef6.png&amp;r=x&amp;s=140" width="20" /> kashifmin
      </a>
    </li>

      <li>
        <a href="/new" id="new_repo" class="tooltipped downwards" title="Create a new repo" aria-label="Create a new repo">
          <span class="octicon octicon-repo-create"></span>
        </a>
      </li>

      <li>
        <a href="/settings/profile" id="account_settings"
          class="tooltipped downwards"
          aria-label="Account settings "
          title="Account settings ">
          <span class="octicon octicon-tools"></span>
        </a>
      </li>
      <li>
        <a class="tooltipped downwards" href="/logout" data-method="post" id="logout" title="Sign out" aria-label="Sign out">
          <span class="octicon octicon-log-out"></span>
        </a>
      </li>

  </ul>

<div class="js-new-dropdown-contents hidden">
  

<ul class="dropdown-menu">
  <li>
    <a href="/new"><span class="octicon octicon-repo-create"></span> New repository</a>
  </li>
  <li>
    <a href="/organizations/new"><span class="octicon octicon-organization"></span> New organization</a>
  </li>



</ul>

</div>


    
  </div>
</div>

      

      




          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        

<ul class="pagehead-actions">

    <li class="subscription">
      <form accept-charset="UTF-8" action="/notifications/subscribe" class="js-social-container" data-autosubmit="true" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="XybXrS3BehyiAYe/MJAntwUExUhHELY12Qjxtz2sQk4=" /></div>  <input id="repository_id" name="repository_id" type="hidden" value="12839156" />

    <div class="select-menu js-menu-container js-select-menu">
      <a class="social-count js-social-count" href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/watchers">
        0
      </a>
      <span class="minibutton select-menu-button with-count js-menu-target" role="button" tabindex="0">
        <span class="js-select-button">
          <span class="octicon octicon-eye-watch"></span>
          Watch
        </span>
      </span>

      <div class="select-menu-modal-holder">
        <div class="select-menu-modal subscription-menu-modal js-menu-content">
          <div class="select-menu-header">
            <span class="select-menu-title">Notification status</span>
            <span class="octicon octicon-remove-close js-menu-close"></span>
          </div> <!-- /.select-menu-header -->

          <div class="select-menu-list js-navigation-container" role="menu">

            <div class="select-menu-item js-navigation-item selected" role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input checked="checked" id="do_included" name="do" type="radio" value="included" />
                <h4>Not watching</h4>
                <span class="description">You only receive notifications for conversations in which you participate or are @mentioned.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-eye-watch"></span>
                  Watch
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

            <div class="select-menu-item js-navigation-item " role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input id="do_subscribed" name="do" type="radio" value="subscribed" />
                <h4>Watching</h4>
                <span class="description">You receive notifications for all conversations in this repository.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-eye-unwatch"></span>
                  Unwatch
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

            <div class="select-menu-item js-navigation-item " role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input id="do_ignore" name="do" type="radio" value="ignore" />
                <h4>Ignoring</h4>
                <span class="description">You do not receive any notifications for conversations in this repository.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-mute"></span>
                  Stop ignoring
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

          </div> <!-- /.select-menu-list -->

        </div> <!-- /.select-menu-modal -->
      </div> <!-- /.select-menu-modal-holder -->
    </div> <!-- /.select-menu -->

</form>
    </li>

  <li>
  

  <div class="js-toggler-container js-social-container starring-container ">
    <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/unstar"
      class="minibutton with-count js-toggler-target star-button starred upwards"
      title="Unstar this repository" data-remote="true" data-method="post" rel="nofollow">
      <span class="octicon octicon-star-delete"></span><span class="text">Unstar</span>
    </a>

    <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/star"
      class="minibutton with-count js-toggler-target star-button unstarred upwards"
      title="Star this repository" data-remote="true" data-method="post" rel="nofollow">
      <span class="octicon octicon-star"></span><span class="text">Star</span>
    </a>

      <a class="social-count js-social-count" href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/stargazers">
        0
      </a>
  </div>

  </li>


        <li>
          <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/fork" class="minibutton with-count js-toggler-target fork-button lighter upwards" title="Fork this repo" rel="nofollow" data-method="post">
            <span class="octicon octicon-git-branch-create"></span><span class="text">Fork</span>
          </a>
          <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/network" class="social-count">24</a>
        </li>


</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="repo-label"><span>public</span></span>
          <span class="mega-octicon octicon-repo-forked"></span>
          <span class="author">
            <a href="/bindassdost" class="url fn" itemprop="url" rel="author"><span itemprop="title">bindassdost</span></a>
          </span>
          <span class="repohead-name-divider">/</span>
          <strong><a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577" class="js-current-repository js-repo-home-link">Bindass-Boost-a110-JB-Kernel-mt6577</a></strong>

          <span class="page-context-loader">
            <img alt="Octocat-spinner-32" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
          </span>

            <span class="fork-flag">
              <span class="text">forked from <a href="/wiko-sources/cink-king">wiko-sources/cink-king</a></span>
            </span>
        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">
      

      <div class="repository-with-sidebar repo-container  ">

        <div class="repository-sidebar">
            

<div class="sunken-menu vertical-right repo-nav js-repo-nav js-repository-container-pjax js-octicon-loaders">
  <div class="sunken-menu-contents">
    <ul class="sunken-menu-group">
      <li class="tooltipped leftwards" title="Code">
        <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577" aria-label="Code" class="selected js-selected-navigation-item sunken-menu-item" data-gotokey="c" data-pjax="true" data-selected-links="repo_source repo_downloads repo_commits repo_tags repo_branches /bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577">
          <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


      <li class="tooltipped leftwards" title="Pull Requests">
        <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/pulls" aria-label="Pull Requests" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-gotokey="p" data-selected-links="repo_pulls /bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/pulls">
            <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull Requests</span>
            <span class='counter'>0</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


        <li class="tooltipped leftwards" title="Wiki">
          <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/wiki" aria-label="Wiki" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="repo_wiki /bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/wiki">
            <span class="octicon octicon-book"></span> <span class="full-word">Wiki</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>
    </ul>
    <div class="sunken-menu-separator"></div>
    <ul class="sunken-menu-group">

      <li class="tooltipped leftwards" title="Pulse">
        <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/pulse" aria-label="Pulse" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="pulse /bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/pulse">
          <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped leftwards" title="Graphs">
        <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/graphs" aria-label="Graphs" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="repo_graphs repo_contributors /bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/graphs">
          <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped leftwards" title="Network">
        <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/network" aria-label="Network" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-selected-links="repo_network /bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/network">
          <span class="octicon octicon-git-branch"></span> <span class="full-word">Network</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>
    </ul>


  </div>
</div>

            <div class="only-with-full-nav">
              

  

<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=clone">
  <h3><strong>HTTPS</strong> clone URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577.git" readonly="readonly">

    <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="https://github.com/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577.git" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="ssh"
  data-url="/users/set_protocol?protocol_selector=ssh&amp;protocol_type=clone">
  <h3><strong>SSH</strong> clone URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="git@github.com:bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577.git" readonly="readonly">

    <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="git@github.com:bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577.git" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=clone">
  <h3><strong>Subversion</strong> checkout URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577" readonly="readonly">

    <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="https://github.com/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>


<p class="clone-options">You can clone with
      <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a>,
      <a href="#" class="js-clone-selector" data-protocol="ssh">SSH</a>,
      or <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>.
  <span class="octicon help tooltipped upwards" title="Get help on which URL is right for you.">
    <a href="https://help.github.com/articles/which-remote-url-should-i-use">
    <span class="octicon octicon-question"></span>
    </a>
  </span>
</p>



              <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/archive/JB.zip"
                 class="minibutton sidebar-button"
                 title="Download this repository as a zip file"
                 rel="nofollow">
                <span class="octicon octicon-cloud-download"></span>
                Download ZIP
              </a>
            </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:72487b66806446fc104dac9c2f518bdf -->

<p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

<a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/find/JB" data-pjax data-hotkey="t" class="js-show-file-finder" style="display:none">Show File Finder</a>

<div class="file-navigation">
  

<div class="select-menu js-menu-container js-select-menu" >
  <span class="minibutton select-menu-button js-menu-target" data-hotkey="w"
    data-master-branch="JB"
    data-ref="JB"
    role="button" aria-label="Switch branches or tags" tabindex="0">
    <span class="octicon octicon-git-branch"></span>
    <i>branch:</i>
    <span class="js-select-button">JB</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax>

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-remove-close js-menu-close"></span>
      </div> <!-- /.select-menu-header -->

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div><!-- /.select-menu-tabs -->
      </div><!-- /.select-menu-filters -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/blob/ICS/kernel/block/bfq.h"
                 data-name="ICS"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target"
                 title="ICS">ICS</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/blob/JB/kernel/block/bfq.h"
                 data-name="JB"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target"
                 title="JB">JB</a>
            </div> <!-- /.select-menu-item -->
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

    </div> <!-- /.select-menu-modal -->
  </div> <!-- /.select-menu-modal-holder -->
</div> <!-- /.select-menu -->

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577" data-branch="JB" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">Bindass-Boost-a110-JB-Kernel-mt6577</span></a></span></span><span class="separator"> / </span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/tree/JB/kernel" data-branch="JB" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">kernel</span></a></span><span class="separator"> / </span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/tree/JB/kernel/block" data-branch="JB" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">block</span></a></span><span class="separator"> / </span><strong class="final-path">bfq.h</strong> <span class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="kernel/block/bfq.h" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>


  <div class="commit commit-loader file-history-tease js-deferred-content" data-url="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/contributors/JB/kernel/block/bfq.h">
    Fetching contributors…

    <div class="participation">
      <p class="loader-loading"><img alt="Octocat-spinner-32-eaf2f5" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32-EAF2F5.gif" width="16" /></p>
      <p class="loader-error">Cannot retrieve contributors at this time</p>
    </div>
  </div>

<div id="files" class="bubble">
  <div class="file">
    <div class="meta">
      <div class="info">
        <span class="icon"><b class="octicon octicon-file-text"></b></span>
        <span class="mode" title="File Mode">file</span>
          <span>618 lines (537 sloc)</span>
        <span>22.13 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
                <a class="minibutton tooltipped upwards"
                   title="Clicking this button will automatically fork this project so you can edit the file"
                   href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/edit/JB/kernel/block/bfq.h"
                   data-method="post" rel="nofollow">Edit</a>
          <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/raw/JB/kernel/block/bfq.h" class="button minibutton " id="raw-url">Raw</a>
            <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/blame/JB/kernel/block/bfq.h" class="button minibutton ">Blame</a>
          <a href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/commits/JB/kernel/block/bfq.h" class="button minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->
          <a class="minibutton danger empty-icon tooltipped downwards"
             href="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/delete/JB/kernel/block/bfq.h"
             title="Fork this project and delete file"
             data-method="post" data-test-id="delete-blob-file" rel="nofollow">
          Delete
        </a>
      </div><!-- /.actions -->

    </div>
        <div class="blob-wrapper data type-c js-blob-data">
        <table class="file-code file-diff">
          <tr class="file-code-line">
            <td class="blob-line-nums">
              <span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>
<span id="L146" rel="#L146">146</span>
<span id="L147" rel="#L147">147</span>
<span id="L148" rel="#L148">148</span>
<span id="L149" rel="#L149">149</span>
<span id="L150" rel="#L150">150</span>
<span id="L151" rel="#L151">151</span>
<span id="L152" rel="#L152">152</span>
<span id="L153" rel="#L153">153</span>
<span id="L154" rel="#L154">154</span>
<span id="L155" rel="#L155">155</span>
<span id="L156" rel="#L156">156</span>
<span id="L157" rel="#L157">157</span>
<span id="L158" rel="#L158">158</span>
<span id="L159" rel="#L159">159</span>
<span id="L160" rel="#L160">160</span>
<span id="L161" rel="#L161">161</span>
<span id="L162" rel="#L162">162</span>
<span id="L163" rel="#L163">163</span>
<span id="L164" rel="#L164">164</span>
<span id="L165" rel="#L165">165</span>
<span id="L166" rel="#L166">166</span>
<span id="L167" rel="#L167">167</span>
<span id="L168" rel="#L168">168</span>
<span id="L169" rel="#L169">169</span>
<span id="L170" rel="#L170">170</span>
<span id="L171" rel="#L171">171</span>
<span id="L172" rel="#L172">172</span>
<span id="L173" rel="#L173">173</span>
<span id="L174" rel="#L174">174</span>
<span id="L175" rel="#L175">175</span>
<span id="L176" rel="#L176">176</span>
<span id="L177" rel="#L177">177</span>
<span id="L178" rel="#L178">178</span>
<span id="L179" rel="#L179">179</span>
<span id="L180" rel="#L180">180</span>
<span id="L181" rel="#L181">181</span>
<span id="L182" rel="#L182">182</span>
<span id="L183" rel="#L183">183</span>
<span id="L184" rel="#L184">184</span>
<span id="L185" rel="#L185">185</span>
<span id="L186" rel="#L186">186</span>
<span id="L187" rel="#L187">187</span>
<span id="L188" rel="#L188">188</span>
<span id="L189" rel="#L189">189</span>
<span id="L190" rel="#L190">190</span>
<span id="L191" rel="#L191">191</span>
<span id="L192" rel="#L192">192</span>
<span id="L193" rel="#L193">193</span>
<span id="L194" rel="#L194">194</span>
<span id="L195" rel="#L195">195</span>
<span id="L196" rel="#L196">196</span>
<span id="L197" rel="#L197">197</span>
<span id="L198" rel="#L198">198</span>
<span id="L199" rel="#L199">199</span>
<span id="L200" rel="#L200">200</span>
<span id="L201" rel="#L201">201</span>
<span id="L202" rel="#L202">202</span>
<span id="L203" rel="#L203">203</span>
<span id="L204" rel="#L204">204</span>
<span id="L205" rel="#L205">205</span>
<span id="L206" rel="#L206">206</span>
<span id="L207" rel="#L207">207</span>
<span id="L208" rel="#L208">208</span>
<span id="L209" rel="#L209">209</span>
<span id="L210" rel="#L210">210</span>
<span id="L211" rel="#L211">211</span>
<span id="L212" rel="#L212">212</span>
<span id="L213" rel="#L213">213</span>
<span id="L214" rel="#L214">214</span>
<span id="L215" rel="#L215">215</span>
<span id="L216" rel="#L216">216</span>
<span id="L217" rel="#L217">217</span>
<span id="L218" rel="#L218">218</span>
<span id="L219" rel="#L219">219</span>
<span id="L220" rel="#L220">220</span>
<span id="L221" rel="#L221">221</span>
<span id="L222" rel="#L222">222</span>
<span id="L223" rel="#L223">223</span>
<span id="L224" rel="#L224">224</span>
<span id="L225" rel="#L225">225</span>
<span id="L226" rel="#L226">226</span>
<span id="L227" rel="#L227">227</span>
<span id="L228" rel="#L228">228</span>
<span id="L229" rel="#L229">229</span>
<span id="L230" rel="#L230">230</span>
<span id="L231" rel="#L231">231</span>
<span id="L232" rel="#L232">232</span>
<span id="L233" rel="#L233">233</span>
<span id="L234" rel="#L234">234</span>
<span id="L235" rel="#L235">235</span>
<span id="L236" rel="#L236">236</span>
<span id="L237" rel="#L237">237</span>
<span id="L238" rel="#L238">238</span>
<span id="L239" rel="#L239">239</span>
<span id="L240" rel="#L240">240</span>
<span id="L241" rel="#L241">241</span>
<span id="L242" rel="#L242">242</span>
<span id="L243" rel="#L243">243</span>
<span id="L244" rel="#L244">244</span>
<span id="L245" rel="#L245">245</span>
<span id="L246" rel="#L246">246</span>
<span id="L247" rel="#L247">247</span>
<span id="L248" rel="#L248">248</span>
<span id="L249" rel="#L249">249</span>
<span id="L250" rel="#L250">250</span>
<span id="L251" rel="#L251">251</span>
<span id="L252" rel="#L252">252</span>
<span id="L253" rel="#L253">253</span>
<span id="L254" rel="#L254">254</span>
<span id="L255" rel="#L255">255</span>
<span id="L256" rel="#L256">256</span>
<span id="L257" rel="#L257">257</span>
<span id="L258" rel="#L258">258</span>
<span id="L259" rel="#L259">259</span>
<span id="L260" rel="#L260">260</span>
<span id="L261" rel="#L261">261</span>
<span id="L262" rel="#L262">262</span>
<span id="L263" rel="#L263">263</span>
<span id="L264" rel="#L264">264</span>
<span id="L265" rel="#L265">265</span>
<span id="L266" rel="#L266">266</span>
<span id="L267" rel="#L267">267</span>
<span id="L268" rel="#L268">268</span>
<span id="L269" rel="#L269">269</span>
<span id="L270" rel="#L270">270</span>
<span id="L271" rel="#L271">271</span>
<span id="L272" rel="#L272">272</span>
<span id="L273" rel="#L273">273</span>
<span id="L274" rel="#L274">274</span>
<span id="L275" rel="#L275">275</span>
<span id="L276" rel="#L276">276</span>
<span id="L277" rel="#L277">277</span>
<span id="L278" rel="#L278">278</span>
<span id="L279" rel="#L279">279</span>
<span id="L280" rel="#L280">280</span>
<span id="L281" rel="#L281">281</span>
<span id="L282" rel="#L282">282</span>
<span id="L283" rel="#L283">283</span>
<span id="L284" rel="#L284">284</span>
<span id="L285" rel="#L285">285</span>
<span id="L286" rel="#L286">286</span>
<span id="L287" rel="#L287">287</span>
<span id="L288" rel="#L288">288</span>
<span id="L289" rel="#L289">289</span>
<span id="L290" rel="#L290">290</span>
<span id="L291" rel="#L291">291</span>
<span id="L292" rel="#L292">292</span>
<span id="L293" rel="#L293">293</span>
<span id="L294" rel="#L294">294</span>
<span id="L295" rel="#L295">295</span>
<span id="L296" rel="#L296">296</span>
<span id="L297" rel="#L297">297</span>
<span id="L298" rel="#L298">298</span>
<span id="L299" rel="#L299">299</span>
<span id="L300" rel="#L300">300</span>
<span id="L301" rel="#L301">301</span>
<span id="L302" rel="#L302">302</span>
<span id="L303" rel="#L303">303</span>
<span id="L304" rel="#L304">304</span>
<span id="L305" rel="#L305">305</span>
<span id="L306" rel="#L306">306</span>
<span id="L307" rel="#L307">307</span>
<span id="L308" rel="#L308">308</span>
<span id="L309" rel="#L309">309</span>
<span id="L310" rel="#L310">310</span>
<span id="L311" rel="#L311">311</span>
<span id="L312" rel="#L312">312</span>
<span id="L313" rel="#L313">313</span>
<span id="L314" rel="#L314">314</span>
<span id="L315" rel="#L315">315</span>
<span id="L316" rel="#L316">316</span>
<span id="L317" rel="#L317">317</span>
<span id="L318" rel="#L318">318</span>
<span id="L319" rel="#L319">319</span>
<span id="L320" rel="#L320">320</span>
<span id="L321" rel="#L321">321</span>
<span id="L322" rel="#L322">322</span>
<span id="L323" rel="#L323">323</span>
<span id="L324" rel="#L324">324</span>
<span id="L325" rel="#L325">325</span>
<span id="L326" rel="#L326">326</span>
<span id="L327" rel="#L327">327</span>
<span id="L328" rel="#L328">328</span>
<span id="L329" rel="#L329">329</span>
<span id="L330" rel="#L330">330</span>
<span id="L331" rel="#L331">331</span>
<span id="L332" rel="#L332">332</span>
<span id="L333" rel="#L333">333</span>
<span id="L334" rel="#L334">334</span>
<span id="L335" rel="#L335">335</span>
<span id="L336" rel="#L336">336</span>
<span id="L337" rel="#L337">337</span>
<span id="L338" rel="#L338">338</span>
<span id="L339" rel="#L339">339</span>
<span id="L340" rel="#L340">340</span>
<span id="L341" rel="#L341">341</span>
<span id="L342" rel="#L342">342</span>
<span id="L343" rel="#L343">343</span>
<span id="L344" rel="#L344">344</span>
<span id="L345" rel="#L345">345</span>
<span id="L346" rel="#L346">346</span>
<span id="L347" rel="#L347">347</span>
<span id="L348" rel="#L348">348</span>
<span id="L349" rel="#L349">349</span>
<span id="L350" rel="#L350">350</span>
<span id="L351" rel="#L351">351</span>
<span id="L352" rel="#L352">352</span>
<span id="L353" rel="#L353">353</span>
<span id="L354" rel="#L354">354</span>
<span id="L355" rel="#L355">355</span>
<span id="L356" rel="#L356">356</span>
<span id="L357" rel="#L357">357</span>
<span id="L358" rel="#L358">358</span>
<span id="L359" rel="#L359">359</span>
<span id="L360" rel="#L360">360</span>
<span id="L361" rel="#L361">361</span>
<span id="L362" rel="#L362">362</span>
<span id="L363" rel="#L363">363</span>
<span id="L364" rel="#L364">364</span>
<span id="L365" rel="#L365">365</span>
<span id="L366" rel="#L366">366</span>
<span id="L367" rel="#L367">367</span>
<span id="L368" rel="#L368">368</span>
<span id="L369" rel="#L369">369</span>
<span id="L370" rel="#L370">370</span>
<span id="L371" rel="#L371">371</span>
<span id="L372" rel="#L372">372</span>
<span id="L373" rel="#L373">373</span>
<span id="L374" rel="#L374">374</span>
<span id="L375" rel="#L375">375</span>
<span id="L376" rel="#L376">376</span>
<span id="L377" rel="#L377">377</span>
<span id="L378" rel="#L378">378</span>
<span id="L379" rel="#L379">379</span>
<span id="L380" rel="#L380">380</span>
<span id="L381" rel="#L381">381</span>
<span id="L382" rel="#L382">382</span>
<span id="L383" rel="#L383">383</span>
<span id="L384" rel="#L384">384</span>
<span id="L385" rel="#L385">385</span>
<span id="L386" rel="#L386">386</span>
<span id="L387" rel="#L387">387</span>
<span id="L388" rel="#L388">388</span>
<span id="L389" rel="#L389">389</span>
<span id="L390" rel="#L390">390</span>
<span id="L391" rel="#L391">391</span>
<span id="L392" rel="#L392">392</span>
<span id="L393" rel="#L393">393</span>
<span id="L394" rel="#L394">394</span>
<span id="L395" rel="#L395">395</span>
<span id="L396" rel="#L396">396</span>
<span id="L397" rel="#L397">397</span>
<span id="L398" rel="#L398">398</span>
<span id="L399" rel="#L399">399</span>
<span id="L400" rel="#L400">400</span>
<span id="L401" rel="#L401">401</span>
<span id="L402" rel="#L402">402</span>
<span id="L403" rel="#L403">403</span>
<span id="L404" rel="#L404">404</span>
<span id="L405" rel="#L405">405</span>
<span id="L406" rel="#L406">406</span>
<span id="L407" rel="#L407">407</span>
<span id="L408" rel="#L408">408</span>
<span id="L409" rel="#L409">409</span>
<span id="L410" rel="#L410">410</span>
<span id="L411" rel="#L411">411</span>
<span id="L412" rel="#L412">412</span>
<span id="L413" rel="#L413">413</span>
<span id="L414" rel="#L414">414</span>
<span id="L415" rel="#L415">415</span>
<span id="L416" rel="#L416">416</span>
<span id="L417" rel="#L417">417</span>
<span id="L418" rel="#L418">418</span>
<span id="L419" rel="#L419">419</span>
<span id="L420" rel="#L420">420</span>
<span id="L421" rel="#L421">421</span>
<span id="L422" rel="#L422">422</span>
<span id="L423" rel="#L423">423</span>
<span id="L424" rel="#L424">424</span>
<span id="L425" rel="#L425">425</span>
<span id="L426" rel="#L426">426</span>
<span id="L427" rel="#L427">427</span>
<span id="L428" rel="#L428">428</span>
<span id="L429" rel="#L429">429</span>
<span id="L430" rel="#L430">430</span>
<span id="L431" rel="#L431">431</span>
<span id="L432" rel="#L432">432</span>
<span id="L433" rel="#L433">433</span>
<span id="L434" rel="#L434">434</span>
<span id="L435" rel="#L435">435</span>
<span id="L436" rel="#L436">436</span>
<span id="L437" rel="#L437">437</span>
<span id="L438" rel="#L438">438</span>
<span id="L439" rel="#L439">439</span>
<span id="L440" rel="#L440">440</span>
<span id="L441" rel="#L441">441</span>
<span id="L442" rel="#L442">442</span>
<span id="L443" rel="#L443">443</span>
<span id="L444" rel="#L444">444</span>
<span id="L445" rel="#L445">445</span>
<span id="L446" rel="#L446">446</span>
<span id="L447" rel="#L447">447</span>
<span id="L448" rel="#L448">448</span>
<span id="L449" rel="#L449">449</span>
<span id="L450" rel="#L450">450</span>
<span id="L451" rel="#L451">451</span>
<span id="L452" rel="#L452">452</span>
<span id="L453" rel="#L453">453</span>
<span id="L454" rel="#L454">454</span>
<span id="L455" rel="#L455">455</span>
<span id="L456" rel="#L456">456</span>
<span id="L457" rel="#L457">457</span>
<span id="L458" rel="#L458">458</span>
<span id="L459" rel="#L459">459</span>
<span id="L460" rel="#L460">460</span>
<span id="L461" rel="#L461">461</span>
<span id="L462" rel="#L462">462</span>
<span id="L463" rel="#L463">463</span>
<span id="L464" rel="#L464">464</span>
<span id="L465" rel="#L465">465</span>
<span id="L466" rel="#L466">466</span>
<span id="L467" rel="#L467">467</span>
<span id="L468" rel="#L468">468</span>
<span id="L469" rel="#L469">469</span>
<span id="L470" rel="#L470">470</span>
<span id="L471" rel="#L471">471</span>
<span id="L472" rel="#L472">472</span>
<span id="L473" rel="#L473">473</span>
<span id="L474" rel="#L474">474</span>
<span id="L475" rel="#L475">475</span>
<span id="L476" rel="#L476">476</span>
<span id="L477" rel="#L477">477</span>
<span id="L478" rel="#L478">478</span>
<span id="L479" rel="#L479">479</span>
<span id="L480" rel="#L480">480</span>
<span id="L481" rel="#L481">481</span>
<span id="L482" rel="#L482">482</span>
<span id="L483" rel="#L483">483</span>
<span id="L484" rel="#L484">484</span>
<span id="L485" rel="#L485">485</span>
<span id="L486" rel="#L486">486</span>
<span id="L487" rel="#L487">487</span>
<span id="L488" rel="#L488">488</span>
<span id="L489" rel="#L489">489</span>
<span id="L490" rel="#L490">490</span>
<span id="L491" rel="#L491">491</span>
<span id="L492" rel="#L492">492</span>
<span id="L493" rel="#L493">493</span>
<span id="L494" rel="#L494">494</span>
<span id="L495" rel="#L495">495</span>
<span id="L496" rel="#L496">496</span>
<span id="L497" rel="#L497">497</span>
<span id="L498" rel="#L498">498</span>
<span id="L499" rel="#L499">499</span>
<span id="L500" rel="#L500">500</span>
<span id="L501" rel="#L501">501</span>
<span id="L502" rel="#L502">502</span>
<span id="L503" rel="#L503">503</span>
<span id="L504" rel="#L504">504</span>
<span id="L505" rel="#L505">505</span>
<span id="L506" rel="#L506">506</span>
<span id="L507" rel="#L507">507</span>
<span id="L508" rel="#L508">508</span>
<span id="L509" rel="#L509">509</span>
<span id="L510" rel="#L510">510</span>
<span id="L511" rel="#L511">511</span>
<span id="L512" rel="#L512">512</span>
<span id="L513" rel="#L513">513</span>
<span id="L514" rel="#L514">514</span>
<span id="L515" rel="#L515">515</span>
<span id="L516" rel="#L516">516</span>
<span id="L517" rel="#L517">517</span>
<span id="L518" rel="#L518">518</span>
<span id="L519" rel="#L519">519</span>
<span id="L520" rel="#L520">520</span>
<span id="L521" rel="#L521">521</span>
<span id="L522" rel="#L522">522</span>
<span id="L523" rel="#L523">523</span>
<span id="L524" rel="#L524">524</span>
<span id="L525" rel="#L525">525</span>
<span id="L526" rel="#L526">526</span>
<span id="L527" rel="#L527">527</span>
<span id="L528" rel="#L528">528</span>
<span id="L529" rel="#L529">529</span>
<span id="L530" rel="#L530">530</span>
<span id="L531" rel="#L531">531</span>
<span id="L532" rel="#L532">532</span>
<span id="L533" rel="#L533">533</span>
<span id="L534" rel="#L534">534</span>
<span id="L535" rel="#L535">535</span>
<span id="L536" rel="#L536">536</span>
<span id="L537" rel="#L537">537</span>
<span id="L538" rel="#L538">538</span>
<span id="L539" rel="#L539">539</span>
<span id="L540" rel="#L540">540</span>
<span id="L541" rel="#L541">541</span>
<span id="L542" rel="#L542">542</span>
<span id="L543" rel="#L543">543</span>
<span id="L544" rel="#L544">544</span>
<span id="L545" rel="#L545">545</span>
<span id="L546" rel="#L546">546</span>
<span id="L547" rel="#L547">547</span>
<span id="L548" rel="#L548">548</span>
<span id="L549" rel="#L549">549</span>
<span id="L550" rel="#L550">550</span>
<span id="L551" rel="#L551">551</span>
<span id="L552" rel="#L552">552</span>
<span id="L553" rel="#L553">553</span>
<span id="L554" rel="#L554">554</span>
<span id="L555" rel="#L555">555</span>
<span id="L556" rel="#L556">556</span>
<span id="L557" rel="#L557">557</span>
<span id="L558" rel="#L558">558</span>
<span id="L559" rel="#L559">559</span>
<span id="L560" rel="#L560">560</span>
<span id="L561" rel="#L561">561</span>
<span id="L562" rel="#L562">562</span>
<span id="L563" rel="#L563">563</span>
<span id="L564" rel="#L564">564</span>
<span id="L565" rel="#L565">565</span>
<span id="L566" rel="#L566">566</span>
<span id="L567" rel="#L567">567</span>
<span id="L568" rel="#L568">568</span>
<span id="L569" rel="#L569">569</span>
<span id="L570" rel="#L570">570</span>
<span id="L571" rel="#L571">571</span>
<span id="L572" rel="#L572">572</span>
<span id="L573" rel="#L573">573</span>
<span id="L574" rel="#L574">574</span>
<span id="L575" rel="#L575">575</span>
<span id="L576" rel="#L576">576</span>
<span id="L577" rel="#L577">577</span>
<span id="L578" rel="#L578">578</span>
<span id="L579" rel="#L579">579</span>
<span id="L580" rel="#L580">580</span>
<span id="L581" rel="#L581">581</span>
<span id="L582" rel="#L582">582</span>
<span id="L583" rel="#L583">583</span>
<span id="L584" rel="#L584">584</span>
<span id="L585" rel="#L585">585</span>
<span id="L586" rel="#L586">586</span>
<span id="L587" rel="#L587">587</span>
<span id="L588" rel="#L588">588</span>
<span id="L589" rel="#L589">589</span>
<span id="L590" rel="#L590">590</span>
<span id="L591" rel="#L591">591</span>
<span id="L592" rel="#L592">592</span>
<span id="L593" rel="#L593">593</span>
<span id="L594" rel="#L594">594</span>
<span id="L595" rel="#L595">595</span>
<span id="L596" rel="#L596">596</span>
<span id="L597" rel="#L597">597</span>
<span id="L598" rel="#L598">598</span>
<span id="L599" rel="#L599">599</span>
<span id="L600" rel="#L600">600</span>
<span id="L601" rel="#L601">601</span>
<span id="L602" rel="#L602">602</span>
<span id="L603" rel="#L603">603</span>
<span id="L604" rel="#L604">604</span>
<span id="L605" rel="#L605">605</span>
<span id="L606" rel="#L606">606</span>
<span id="L607" rel="#L607">607</span>
<span id="L608" rel="#L608">608</span>
<span id="L609" rel="#L609">609</span>
<span id="L610" rel="#L610">610</span>
<span id="L611" rel="#L611">611</span>
<span id="L612" rel="#L612">612</span>
<span id="L613" rel="#L613">613</span>
<span id="L614" rel="#L614">614</span>
<span id="L615" rel="#L615">615</span>
<span id="L616" rel="#L616">616</span>
<span id="L617" rel="#L617">617</span>

            </td>
            <td class="blob-line-code">
                    <div class="code-body highlight"><pre><div class='line' id='LC1'><span class="cm">/*</span></div><div class='line' id='LC2'><span class="cm"> * BFQ-v5r1 for 3.4.0: data structures and common functions prototypes.</span></div><div class='line' id='LC3'><span class="cm"> *</span></div><div class='line' id='LC4'><span class="cm"> * Based on ideas and code from CFQ:</span></div><div class='line' id='LC5'><span class="cm"> * Copyright (C) 2003 Jens Axboe &lt;axboe@kernel.dk&gt;</span></div><div class='line' id='LC6'><span class="cm"> *</span></div><div class='line' id='LC7'><span class="cm"> * Copyright (C) 2008 Fabio Checconi &lt;fabio@gandalf.sssup.it&gt;</span></div><div class='line' id='LC8'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      Paolo Valente &lt;paolo.valente@unimore.it&gt;</span></div><div class='line' id='LC9'><span class="cm"> *</span></div><div class='line' id='LC10'><span class="cm"> * Copyright (C) 2010 Paolo Valente &lt;paolo.valente@unimore.it&gt;</span></div><div class='line' id='LC11'><span class="cm"> */</span></div><div class='line' id='LC12'><br/></div><div class='line' id='LC13'><span class="cp">#ifndef _BFQ_H</span></div><div class='line' id='LC14'><span class="cp">#define _BFQ_H</span></div><div class='line' id='LC15'><br/></div><div class='line' id='LC16'><span class="cp">#include &lt;linux/blktrace_api.h&gt;</span></div><div class='line' id='LC17'><span class="cp">#include &lt;linux/hrtimer.h&gt;</span></div><div class='line' id='LC18'><span class="cp">#include &lt;linux/ioprio.h&gt;</span></div><div class='line' id='LC19'><span class="cp">#include &lt;linux/rbtree.h&gt;</span></div><div class='line' id='LC20'><br/></div><div class='line' id='LC21'><span class="cp">#define BFQ_IOPRIO_CLASSES&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3</span></div><div class='line' id='LC22'><span class="cp">#define BFQ_CL_IDLE_TIMEOUT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;HZ/5</span></div><div class='line' id='LC23'><br/></div><div class='line' id='LC24'><span class="cp">#define BFQ_MIN_WEIGHT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1</span></div><div class='line' id='LC25'><span class="cp">#define BFQ_MAX_WEIGHT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1000</span></div><div class='line' id='LC26'><br/></div><div class='line' id='LC27'><span class="cp">#define BFQ_DEFAULT_GRP_WEIGHT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10</span></div><div class='line' id='LC28'><span class="cp">#define BFQ_DEFAULT_GRP_IOPRIO&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0</span></div><div class='line' id='LC29'><span class="cp">#define BFQ_DEFAULT_GRP_CLASS&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;IOPRIO_CLASS_BE</span></div><div class='line' id='LC30'><br/></div><div class='line' id='LC31'><span class="k">struct</span> <span class="n">bfq_entity</span><span class="p">;</span></div><div class='line' id='LC32'><br/></div><div class='line' id='LC33'><span class="cm">/**</span></div><div class='line' id='LC34'><span class="cm"> * struct bfq_service_tree - per ioprio_class service tree.</span></div><div class='line' id='LC35'><span class="cm"> * @active: tree for active entities (i.e., those backlogged).</span></div><div class='line' id='LC36'><span class="cm"> * @idle: tree for idle entities (i.e., those not backlogged, with V &lt;= F_i).</span></div><div class='line' id='LC37'><span class="cm"> * @first_idle: idle entity with minimum F_i.</span></div><div class='line' id='LC38'><span class="cm"> * @last_idle: idle entity with maximum F_i.</span></div><div class='line' id='LC39'><span class="cm"> * @vtime: scheduler virtual time.</span></div><div class='line' id='LC40'><span class="cm"> * @wsum: scheduler weight sum; active and idle entities contribute to it.</span></div><div class='line' id='LC41'><span class="cm"> *</span></div><div class='line' id='LC42'><span class="cm"> * Each service tree represents a B-WF2Q+ scheduler on its own.  Each</span></div><div class='line' id='LC43'><span class="cm"> * ioprio_class has its own independent scheduler, and so its own</span></div><div class='line' id='LC44'><span class="cm"> * bfq_service_tree.  All the fields are protected by the queue lock</span></div><div class='line' id='LC45'><span class="cm"> * of the containing bfqd.</span></div><div class='line' id='LC46'><span class="cm"> */</span></div><div class='line' id='LC47'><span class="k">struct</span> <span class="n">bfq_service_tree</span> <span class="p">{</span></div><div class='line' id='LC48'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">rb_root</span> <span class="n">active</span><span class="p">;</span></div><div class='line' id='LC49'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">rb_root</span> <span class="n">idle</span><span class="p">;</span></div><div class='line' id='LC50'><br/></div><div class='line' id='LC51'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_entity</span> <span class="o">*</span><span class="n">first_idle</span><span class="p">;</span></div><div class='line' id='LC52'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_entity</span> <span class="o">*</span><span class="n">last_idle</span><span class="p">;</span></div><div class='line' id='LC53'><br/></div><div class='line' id='LC54'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">vtime</span><span class="p">;</span></div><div class='line' id='LC55'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">wsum</span><span class="p">;</span></div><div class='line' id='LC56'><span class="p">};</span></div><div class='line' id='LC57'><br/></div><div class='line' id='LC58'><span class="cm">/**</span></div><div class='line' id='LC59'><span class="cm"> * struct bfq_sched_data - multi-class scheduler.</span></div><div class='line' id='LC60'><span class="cm"> * @active_entity: entity under service.</span></div><div class='line' id='LC61'><span class="cm"> * @next_active: head-of-the-line entity in the scheduler.</span></div><div class='line' id='LC62'><span class="cm"> * @service_tree: array of service trees, one per ioprio_class.</span></div><div class='line' id='LC63'><span class="cm"> *</span></div><div class='line' id='LC64'><span class="cm"> * bfq_sched_data is the basic scheduler queue.  It supports three</span></div><div class='line' id='LC65'><span class="cm"> * ioprio_classes, and can be used either as a toplevel queue or as</span></div><div class='line' id='LC66'><span class="cm"> * an intermediate queue on a hierarchical setup.</span></div><div class='line' id='LC67'><span class="cm"> * @next_active points to the active entity of the sched_data service</span></div><div class='line' id='LC68'><span class="cm"> * trees that will be scheduled next.</span></div><div class='line' id='LC69'><span class="cm"> *</span></div><div class='line' id='LC70'><span class="cm"> * The supported ioprio_classes are the same as in CFQ, in descending</span></div><div class='line' id='LC71'><span class="cm"> * priority order, IOPRIO_CLASS_RT, IOPRIO_CLASS_BE, IOPRIO_CLASS_IDLE.</span></div><div class='line' id='LC72'><span class="cm"> * Requests from higher priority queues are served before all the</span></div><div class='line' id='LC73'><span class="cm"> * requests from lower priority queues; among requests of the same</span></div><div class='line' id='LC74'><span class="cm"> * queue requests are served according to B-WF2Q+.</span></div><div class='line' id='LC75'><span class="cm"> * All the fields are protected by the queue lock of the containing bfqd.</span></div><div class='line' id='LC76'><span class="cm"> */</span></div><div class='line' id='LC77'><span class="k">struct</span> <span class="n">bfq_sched_data</span> <span class="p">{</span></div><div class='line' id='LC78'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_entity</span> <span class="o">*</span><span class="n">active_entity</span><span class="p">;</span></div><div class='line' id='LC79'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_entity</span> <span class="o">*</span><span class="n">next_active</span><span class="p">;</span></div><div class='line' id='LC80'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_service_tree</span> <span class="n">service_tree</span><span class="p">[</span><span class="n">BFQ_IOPRIO_CLASSES</span><span class="p">];</span></div><div class='line' id='LC81'><span class="p">};</span></div><div class='line' id='LC82'><br/></div><div class='line' id='LC83'><span class="cm">/**</span></div><div class='line' id='LC84'><span class="cm"> * struct bfq_entity - schedulable entity.</span></div><div class='line' id='LC85'><span class="cm"> * @rb_node: service_tree member.</span></div><div class='line' id='LC86'><span class="cm"> * @on_st: flag, true if the entity is on a tree (either the active or</span></div><div class='line' id='LC87'><span class="cm"> *         the idle one of its service_tree).</span></div><div class='line' id='LC88'><span class="cm"> * @finish: B-WF2Q+ finish timestamp (aka F_i).</span></div><div class='line' id='LC89'><span class="cm"> * @start: B-WF2Q+ start timestamp (aka S_i).</span></div><div class='line' id='LC90'><span class="cm"> * @tree: tree the entity is enqueued into; %NULL if not on a tree.</span></div><div class='line' id='LC91'><span class="cm"> * @min_start: minimum start time of the (active) subtree rooted at</span></div><div class='line' id='LC92'><span class="cm"> *             this entity; used for O(log N) lookups into active trees.</span></div><div class='line' id='LC93'><span class="cm"> * @service: service received during the last round of service.</span></div><div class='line' id='LC94'><span class="cm"> * @budget: budget used to calculate F_i; F_i = S_i + @budget / @weight.</span></div><div class='line' id='LC95'><span class="cm"> * @weight: weight of the queue</span></div><div class='line' id='LC96'><span class="cm"> * @parent: parent entity, for hierarchical scheduling.</span></div><div class='line' id='LC97'><span class="cm"> * @my_sched_data: for non-leaf nodes in the cgroup hierarchy, the</span></div><div class='line' id='LC98'><span class="cm"> *                 associated scheduler queue, %NULL on leaf nodes.</span></div><div class='line' id='LC99'><span class="cm"> * @sched_data: the scheduler queue this entity belongs to.</span></div><div class='line' id='LC100'><span class="cm"> * @ioprio: the ioprio in use.</span></div><div class='line' id='LC101'><span class="cm"> * @new_weight: when a weight change is requested, the new weight value.</span></div><div class='line' id='LC102'><span class="cm"> * @orig_weight: original weight, used to implement weight boosting</span></div><div class='line' id='LC103'><span class="cm"> * @new_ioprio: when an ioprio change is requested, the new ioprio value.</span></div><div class='line' id='LC104'><span class="cm"> * @ioprio_class: the ioprio_class in use.</span></div><div class='line' id='LC105'><span class="cm"> * @new_ioprio_class: when an ioprio_class change is requested, the new</span></div><div class='line' id='LC106'><span class="cm"> *                    ioprio_class value.</span></div><div class='line' id='LC107'><span class="cm"> * @ioprio_changed: flag, true when the user requested a weight, ioprio or</span></div><div class='line' id='LC108'><span class="cm"> *                  ioprio_class change.</span></div><div class='line' id='LC109'><span class="cm"> *</span></div><div class='line' id='LC110'><span class="cm"> * A bfq_entity is used to represent either a bfq_queue (leaf node in the</span></div><div class='line' id='LC111'><span class="cm"> * cgroup hierarchy) or a bfq_group into the upper level scheduler.  Each</span></div><div class='line' id='LC112'><span class="cm"> * entity belongs to the sched_data of the parent group in the cgroup</span></div><div class='line' id='LC113'><span class="cm"> * hierarchy.  Non-leaf entities have also their own sched_data, stored</span></div><div class='line' id='LC114'><span class="cm"> * in @my_sched_data.</span></div><div class='line' id='LC115'><span class="cm"> *</span></div><div class='line' id='LC116'><span class="cm"> * Each entity stores independently its priority values; this would</span></div><div class='line' id='LC117'><span class="cm"> * allow different weights on different devices, but this</span></div><div class='line' id='LC118'><span class="cm"> * functionality is not exported to userspace by now.  Priorities and</span></div><div class='line' id='LC119'><span class="cm"> * weights are updated lazily, first storing the new values into the</span></div><div class='line' id='LC120'><span class="cm"> * new_* fields, then setting the @ioprio_changed flag.  As soon as</span></div><div class='line' id='LC121'><span class="cm"> * there is a transition in the entity state that allows the priority</span></div><div class='line' id='LC122'><span class="cm"> * update to take place the effective and the requested priority</span></div><div class='line' id='LC123'><span class="cm"> * values are synchronized.</span></div><div class='line' id='LC124'><span class="cm"> *</span></div><div class='line' id='LC125'><span class="cm"> * Unless cgroups are used, the weight value is calculated from the</span></div><div class='line' id='LC126'><span class="cm"> * ioprio to export the same interface as CFQ.  When dealing with</span></div><div class='line' id='LC127'><span class="cm"> * ``well-behaved&#39;&#39; queues (i.e., queues that do not spend too much</span></div><div class='line' id='LC128'><span class="cm"> * time to consume their budget and have true sequential behavior, and</span></div><div class='line' id='LC129'><span class="cm"> * when there are no external factors breaking anticipation) the</span></div><div class='line' id='LC130'><span class="cm"> * relative weights at each level of the cgroups hierarchy should be</span></div><div class='line' id='LC131'><span class="cm"> * guaranteed.  All the fields are protected by the queue lock of the</span></div><div class='line' id='LC132'><span class="cm"> * containing bfqd.</span></div><div class='line' id='LC133'><span class="cm"> */</span></div><div class='line' id='LC134'><span class="k">struct</span> <span class="n">bfq_entity</span> <span class="p">{</span></div><div class='line' id='LC135'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">rb_node</span> <span class="n">rb_node</span><span class="p">;</span></div><div class='line' id='LC136'><br/></div><div class='line' id='LC137'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">on_st</span><span class="p">;</span></div><div class='line' id='LC138'><br/></div><div class='line' id='LC139'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">finish</span><span class="p">;</span></div><div class='line' id='LC140'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">start</span><span class="p">;</span></div><div class='line' id='LC141'><br/></div><div class='line' id='LC142'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">rb_root</span> <span class="o">*</span><span class="n">tree</span><span class="p">;</span></div><div class='line' id='LC143'><br/></div><div class='line' id='LC144'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">min_start</span><span class="p">;</span></div><div class='line' id='LC145'><br/></div><div class='line' id='LC146'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">service</span><span class="p">,</span> <span class="n">budget</span><span class="p">;</span></div><div class='line' id='LC147'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">short</span> <span class="n">weight</span><span class="p">,</span> <span class="n">new_weight</span><span class="p">;</span></div><div class='line' id='LC148'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">short</span> <span class="n">orig_weight</span><span class="p">;</span></div><div class='line' id='LC149'><br/></div><div class='line' id='LC150'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_entity</span> <span class="o">*</span><span class="n">parent</span><span class="p">;</span></div><div class='line' id='LC151'><br/></div><div class='line' id='LC152'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_sched_data</span> <span class="o">*</span><span class="n">my_sched_data</span><span class="p">;</span></div><div class='line' id='LC153'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_sched_data</span> <span class="o">*</span><span class="n">sched_data</span><span class="p">;</span></div><div class='line' id='LC154'><br/></div><div class='line' id='LC155'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">short</span> <span class="n">ioprio</span><span class="p">,</span> <span class="n">new_ioprio</span><span class="p">;</span></div><div class='line' id='LC156'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">short</span> <span class="n">ioprio_class</span><span class="p">,</span> <span class="n">new_ioprio_class</span><span class="p">;</span></div><div class='line' id='LC157'><br/></div><div class='line' id='LC158'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">ioprio_changed</span><span class="p">;</span></div><div class='line' id='LC159'><span class="p">};</span></div><div class='line' id='LC160'><br/></div><div class='line' id='LC161'><span class="k">struct</span> <span class="n">bfq_group</span><span class="p">;</span></div><div class='line' id='LC162'><br/></div><div class='line' id='LC163'><span class="cm">/**</span></div><div class='line' id='LC164'><span class="cm"> * struct bfq_queue - leaf schedulable entity.</span></div><div class='line' id='LC165'><span class="cm"> * @ref: reference counter.</span></div><div class='line' id='LC166'><span class="cm"> * @bfqd: parent bfq_data.</span></div><div class='line' id='LC167'><span class="cm"> * @new_bfqq: shared bfq_queue if queue is cooperating with</span></div><div class='line' id='LC168'><span class="cm"> *           one or more other queues.</span></div><div class='line' id='LC169'><span class="cm"> * @pos_node: request-position tree member (see bfq_data&#39;s @rq_pos_tree).</span></div><div class='line' id='LC170'><span class="cm"> * @pos_root: request-position tree root (see bfq_data&#39;s @rq_pos_tree).</span></div><div class='line' id='LC171'><span class="cm"> * @sort_list: sorted list of pending requests.</span></div><div class='line' id='LC172'><span class="cm"> * @next_rq: if fifo isn&#39;t expired, next request to serve.</span></div><div class='line' id='LC173'><span class="cm"> * @queued: nr of requests queued in @sort_list.</span></div><div class='line' id='LC174'><span class="cm"> * @allocated: currently allocated requests.</span></div><div class='line' id='LC175'><span class="cm"> * @meta_pending: pending metadata requests.</span></div><div class='line' id='LC176'><span class="cm"> * @fifo: fifo list of requests in sort_list.</span></div><div class='line' id='LC177'><span class="cm"> * @entity: entity representing this queue in the scheduler.</span></div><div class='line' id='LC178'><span class="cm"> * @max_budget: maximum budget allowed from the feedback mechanism.</span></div><div class='line' id='LC179'><span class="cm"> * @budget_timeout: budget expiration (in jiffies).</span></div><div class='line' id='LC180'><span class="cm"> * @dispatched: number of requests on the dispatch list or inside driver.</span></div><div class='line' id='LC181'><span class="cm"> * @org_ioprio: saved ioprio during boosted periods.</span></div><div class='line' id='LC182'><span class="cm"> * @flags: status flags.</span></div><div class='line' id='LC183'><span class="cm"> * @bfqq_list: node for active/idle bfqq list inside our bfqd.</span></div><div class='line' id='LC184'><span class="cm"> * @seek_samples: number of seeks sampled</span></div><div class='line' id='LC185'><span class="cm"> * @seek_total: sum of the distances of the seeks sampled</span></div><div class='line' id='LC186'><span class="cm"> * @seek_mean: mean seek distance</span></div><div class='line' id='LC187'><span class="cm"> * @last_request_pos: position of the last request enqueued</span></div><div class='line' id='LC188'><span class="cm"> * @pid: pid of the process owning the queue, used for logging purposes.</span></div><div class='line' id='LC189'><span class="cm"> * @last_rais_start_time: last (idle -&gt; weight-raised) transition attempt</span></div><div class='line' id='LC190'><span class="cm"> * @raising_cur_max_time: current max raising time for this queue</span></div><div class='line' id='LC191'><span class="cm"> * @bic: pointer to the bfq_io_cq owning the bfq_queue, set to %NULL if the</span></div><div class='line' id='LC192'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; queue is shared</span></div><div class='line' id='LC193'><span class="cm"> *</span></div><div class='line' id='LC194'><span class="cm"> * A bfq_queue is a leaf request queue; it can be associated to an io_context</span></div><div class='line' id='LC195'><span class="cm"> * or more (if it is an async one).  @cgroup holds a reference to the</span></div><div class='line' id='LC196'><span class="cm"> * cgroup, to be sure that it does not disappear while a bfqq still</span></div><div class='line' id='LC197'><span class="cm"> * references it (mostly to avoid races between request issuing and task</span></div><div class='line' id='LC198'><span class="cm"> * migration followed by cgroup distruction).</span></div><div class='line' id='LC199'><span class="cm"> * All the fields are protected by the queue lock of the containing bfqd.</span></div><div class='line' id='LC200'><span class="cm"> */</span></div><div class='line' id='LC201'><span class="k">struct</span> <span class="n">bfq_queue</span> <span class="p">{</span></div><div class='line' id='LC202'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">atomic_t</span> <span class="n">ref</span><span class="p">;</span></div><div class='line' id='LC203'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">*</span><span class="n">bfqd</span><span class="p">;</span></div><div class='line' id='LC204'><br/></div><div class='line' id='LC205'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* fields for cooperating queues handling */</span></div><div class='line' id='LC206'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">new_bfqq</span><span class="p">;</span></div><div class='line' id='LC207'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">rb_node</span> <span class="n">pos_node</span><span class="p">;</span></div><div class='line' id='LC208'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">rb_root</span> <span class="o">*</span><span class="n">pos_root</span><span class="p">;</span></div><div class='line' id='LC209'><br/></div><div class='line' id='LC210'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">rb_root</span> <span class="n">sort_list</span><span class="p">;</span></div><div class='line' id='LC211'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">request</span> <span class="o">*</span><span class="n">next_rq</span><span class="p">;</span></div><div class='line' id='LC212'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">queued</span><span class="p">[</span><span class="mi">2</span><span class="p">];</span></div><div class='line' id='LC213'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">allocated</span><span class="p">[</span><span class="mi">2</span><span class="p">];</span></div><div class='line' id='LC214'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">meta_pending</span><span class="p">;</span></div><div class='line' id='LC215'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">list_head</span> <span class="n">fifo</span><span class="p">;</span></div><div class='line' id='LC216'><br/></div><div class='line' id='LC217'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_entity</span> <span class="n">entity</span><span class="p">;</span></div><div class='line' id='LC218'><br/></div><div class='line' id='LC219'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">max_budget</span><span class="p">;</span></div><div class='line' id='LC220'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">budget_timeout</span><span class="p">;</span></div><div class='line' id='LC221'><br/></div><div class='line' id='LC222'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">dispatched</span><span class="p">;</span></div><div class='line' id='LC223'><br/></div><div class='line' id='LC224'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">short</span> <span class="n">org_ioprio</span><span class="p">;</span></div><div class='line' id='LC225'><br/></div><div class='line' id='LC226'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">flags</span><span class="p">;</span></div><div class='line' id='LC227'><br/></div><div class='line' id='LC228'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">list_head</span> <span class="n">bfqq_list</span><span class="p">;</span></div><div class='line' id='LC229'><br/></div><div class='line' id='LC230'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">seek_samples</span><span class="p">;</span></div><div class='line' id='LC231'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">seek_total</span><span class="p">;</span></div><div class='line' id='LC232'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">sector_t</span> <span class="n">seek_mean</span><span class="p">;</span></div><div class='line' id='LC233'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">sector_t</span> <span class="n">last_request_pos</span><span class="p">;</span></div><div class='line' id='LC234'><br/></div><div class='line' id='LC235'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">pid_t</span> <span class="n">pid</span><span class="p">;</span></div><div class='line' id='LC236'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_io_cq</span> <span class="o">*</span><span class="n">bic</span><span class="p">;</span></div><div class='line' id='LC237'><br/></div><div class='line' id='LC238'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* weight-raising fields */</span></div><div class='line' id='LC239'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">raising_cur_max_time</span><span class="p">;</span></div><div class='line' id='LC240'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">last_rais_start_finish</span><span class="p">,</span> <span class="n">soft_rt_next_start</span><span class="p">;</span></div><div class='line' id='LC241'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">raising_coeff</span><span class="p">;</span></div><div class='line' id='LC242'><span class="p">};</span></div><div class='line' id='LC243'><br/></div><div class='line' id='LC244'><span class="cm">/**</span></div><div class='line' id='LC245'><span class="cm"> * struct bfq_ttime - per process thinktime stats.</span></div><div class='line' id='LC246'><span class="cm"> * @ttime_total: total process thinktime</span></div><div class='line' id='LC247'><span class="cm"> * @ttime_samples: number of thinktime samples</span></div><div class='line' id='LC248'><span class="cm"> * @ttime_mean: average process thinktime</span></div><div class='line' id='LC249'><span class="cm"> */</span></div><div class='line' id='LC250'><span class="k">struct</span> <span class="n">bfq_ttime</span> <span class="p">{</span></div><div class='line' id='LC251'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">last_end_request</span><span class="p">;</span></div><div class='line' id='LC252'><br/></div><div class='line' id='LC253'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">ttime_total</span><span class="p">;</span></div><div class='line' id='LC254'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">ttime_samples</span><span class="p">;</span></div><div class='line' id='LC255'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">ttime_mean</span><span class="p">;</span></div><div class='line' id='LC256'><span class="p">};</span></div><div class='line' id='LC257'><br/></div><div class='line' id='LC258'><span class="cm">/**</span></div><div class='line' id='LC259'><span class="cm"> * struct bfq_io_cq - per (request_queue, io_context) structure.</span></div><div class='line' id='LC260'><span class="cm"> * @icq: associated io_cq structure</span></div><div class='line' id='LC261'><span class="cm"> * @bfqq: array of two process queues, the sync and the async</span></div><div class='line' id='LC262'><span class="cm"> * @ttime: associated @bfq_ttime struct</span></div><div class='line' id='LC263'><span class="cm"> * @raising_time_left: snapshot of the time left before weight raising ends</span></div><div class='line' id='LC264'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       for the sync queue associated to this process; this</span></div><div class='line' id='LC265'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       snapshot is taken to remember this value while the weight</span></div><div class='line' id='LC266'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       raising is suspended because the queue is merged with a</span></div><div class='line' id='LC267'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       shared queue, and is used to set @raising_cur_max_time</span></div><div class='line' id='LC268'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       when the queue is split from the shared queue and its</span></div><div class='line' id='LC269'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       weight is raised again</span></div><div class='line' id='LC270'><span class="cm"> * @saved_idle_window: same purpose as the previous field for the idle window</span></div><div class='line' id='LC271'><span class="cm"> */</span></div><div class='line' id='LC272'><span class="k">struct</span> <span class="n">bfq_io_cq</span> <span class="p">{</span></div><div class='line' id='LC273'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">io_cq</span> <span class="n">icq</span><span class="p">;</span> <span class="cm">/* must be the first member */</span></div><div class='line' id='LC274'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">bfqq</span><span class="p">[</span><span class="mi">2</span><span class="p">];</span></div><div class='line' id='LC275'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_ttime</span> <span class="n">ttime</span><span class="p">;</span></div><div class='line' id='LC276'><br/></div><div class='line' id='LC277'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">raising_time_left</span><span class="p">;</span></div><div class='line' id='LC278'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">saved_idle_window</span><span class="p">;</span></div><div class='line' id='LC279'><span class="p">};</span></div><div class='line' id='LC280'><br/></div><div class='line' id='LC281'><span class="cm">/**</span></div><div class='line' id='LC282'><span class="cm"> * struct bfq_data - per device data structure.</span></div><div class='line' id='LC283'><span class="cm"> * @queue: request queue for the managed device.</span></div><div class='line' id='LC284'><span class="cm"> * @root_group: root bfq_group for the device.</span></div><div class='line' id='LC285'><span class="cm"> * @rq_pos_tree: rbtree sorted by next_request position,</span></div><div class='line' id='LC286'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;used when determining if two or more queues</span></div><div class='line' id='LC287'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;have interleaving requests (see bfq_close_cooperator).</span></div><div class='line' id='LC288'><span class="cm"> * @busy_queues: number of bfq_queues containing requests (including the</span></div><div class='line' id='LC289'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; queue under service, even if it is idling).</span></div><div class='line' id='LC290'><span class="cm"> * @queued: number of queued requests.</span></div><div class='line' id='LC291'><span class="cm"> * @rq_in_driver: number of requests dispatched and waiting for completion.</span></div><div class='line' id='LC292'><span class="cm"> * @sync_flight: number of sync requests in the driver.</span></div><div class='line' id='LC293'><span class="cm"> * @max_rq_in_driver: max number of reqs in driver in the last @hw_tag_samples</span></div><div class='line' id='LC294'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      completed requests .</span></div><div class='line' id='LC295'><span class="cm"> * @hw_tag_samples: nr of samples used to calculate hw_tag.</span></div><div class='line' id='LC296'><span class="cm"> * @hw_tag: flag set to one if the driver is showing a queueing behavior.</span></div><div class='line' id='LC297'><span class="cm"> * @budgets_assigned: number of budgets assigned.</span></div><div class='line' id='LC298'><span class="cm"> * @idle_slice_timer: timer set when idling for the next sequential request</span></div><div class='line' id='LC299'><span class="cm"> *                    from the queue under service.</span></div><div class='line' id='LC300'><span class="cm"> * @unplug_work: delayed work to restart dispatching on the request queue.</span></div><div class='line' id='LC301'><span class="cm"> * @active_queue: bfq_queue under service.</span></div><div class='line' id='LC302'><span class="cm"> * @active_bic: bfq_io_cq (bic) associated with the @active_queue.</span></div><div class='line' id='LC303'><span class="cm"> * @last_position: on-disk position of the last served request.</span></div><div class='line' id='LC304'><span class="cm"> * @last_budget_start: beginning of the last budget.</span></div><div class='line' id='LC305'><span class="cm"> * @last_idling_start: beginning of the last idle slice.</span></div><div class='line' id='LC306'><span class="cm"> * @peak_rate: peak transfer rate observed for a budget.</span></div><div class='line' id='LC307'><span class="cm"> * @peak_rate_samples: number of samples used to calculate @peak_rate.</span></div><div class='line' id='LC308'><span class="cm"> * @bfq_max_budget: maximum budget allotted to a bfq_queue before rescheduling.</span></div><div class='line' id='LC309'><span class="cm"> * @group_list: list of all the bfq_groups active on the device.</span></div><div class='line' id='LC310'><span class="cm"> * @active_list: list of all the bfq_queues active on the device.</span></div><div class='line' id='LC311'><span class="cm"> * @idle_list: list of all the bfq_queues idle on the device.</span></div><div class='line' id='LC312'><span class="cm"> * @bfq_quantum: max number of requests dispatched per dispatch round.</span></div><div class='line' id='LC313'><span class="cm"> * @bfq_fifo_expire: timeout for async/sync requests; when it expires</span></div><div class='line' id='LC314'><span class="cm"> *                   requests are served in fifo order.</span></div><div class='line' id='LC315'><span class="cm"> * @bfq_back_penalty: weight of backward seeks wrt forward ones.</span></div><div class='line' id='LC316'><span class="cm"> * @bfq_back_max: maximum allowed backward seek.</span></div><div class='line' id='LC317'><span class="cm"> * @bfq_slice_idle: maximum idling time.</span></div><div class='line' id='LC318'><span class="cm"> * @bfq_user_max_budget: user-configured max budget value (0 for auto-tuning).</span></div><div class='line' id='LC319'><span class="cm"> * @bfq_max_budget_async_rq: maximum budget (in nr of requests) allotted to</span></div><div class='line' id='LC320'><span class="cm"> *                           async queues.</span></div><div class='line' id='LC321'><span class="cm"> * @bfq_timeout: timeout for bfq_queues to consume their budget; used to</span></div><div class='line' id='LC322'><span class="cm"> *               to prevent seeky queues to impose long latencies to well</span></div><div class='line' id='LC323'><span class="cm"> *               behaved ones (this also implies that seeky queues cannot</span></div><div class='line' id='LC324'><span class="cm"> *               receive guarantees in the service domain; after a timeout</span></div><div class='line' id='LC325'><span class="cm"> *               they are charged for the whole allocated budget, to try</span></div><div class='line' id='LC326'><span class="cm"> *               to preserve a behavior reasonably fair among them, but</span></div><div class='line' id='LC327'><span class="cm"> *               without service-domain guarantees).</span></div><div class='line' id='LC328'><span class="cm"> * @bfq_raising_coeff: Maximum factor by which the weight of a boosted</span></div><div class='line' id='LC329'><span class="cm"> *                            queue is multiplied</span></div><div class='line' id='LC330'><span class="cm"> * @bfq_raising_max_time: maximum duration of a weight-raising period (jiffies)</span></div><div class='line' id='LC331'><span class="cm"> * @bfq_raising_rt_max_time: maximum duration for soft real-time processes</span></div><div class='line' id='LC332'><span class="cm"> * @bfq_raising_min_idle_time: minimum idle period after which weight-raising</span></div><div class='line' id='LC333'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       may be reactivated for a queue (in jiffies)</span></div><div class='line' id='LC334'><span class="cm"> * @bfq_raising_min_inter_arr_async: minimum period between request arrivals</span></div><div class='line' id='LC335'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     after which weight-raising may be</span></div><div class='line' id='LC336'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     reactivated for an already busy queue</span></div><div class='line' id='LC337'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     (in jiffies)</span></div><div class='line' id='LC338'><span class="cm"> * @bfq_raising_max_softrt_rate: max service-rate for a soft real-time queue,</span></div><div class='line' id='LC339'><span class="cm"> *&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;         sectors per seconds</span></div><div class='line' id='LC340'><span class="cm"> * @RT_prod: cached value of the product R*T used for computing the maximum</span></div><div class='line' id='LC341'><span class="cm"> * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     duration of the weight raising automatically</span></div><div class='line' id='LC342'><span class="cm"> * @oom_bfqq: fallback dummy bfqq for extreme OOM conditions</span></div><div class='line' id='LC343'><span class="cm"> *</span></div><div class='line' id='LC344'><span class="cm"> * All the fields are protected by the @queue lock.</span></div><div class='line' id='LC345'><span class="cm"> */</span></div><div class='line' id='LC346'><span class="k">struct</span> <span class="n">bfq_data</span> <span class="p">{</span></div><div class='line' id='LC347'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">request_queue</span> <span class="o">*</span><span class="n">queue</span><span class="p">;</span></div><div class='line' id='LC348'><br/></div><div class='line' id='LC349'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_group</span> <span class="o">*</span><span class="n">root_group</span><span class="p">;</span></div><div class='line' id='LC350'><br/></div><div class='line' id='LC351'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">rb_root</span> <span class="n">rq_pos_tree</span><span class="p">;</span></div><div class='line' id='LC352'><br/></div><div class='line' id='LC353'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">busy_queues</span><span class="p">;</span></div><div class='line' id='LC354'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">queued</span><span class="p">;</span></div><div class='line' id='LC355'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">rq_in_driver</span><span class="p">;</span></div><div class='line' id='LC356'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">sync_flight</span><span class="p">;</span></div><div class='line' id='LC357'><br/></div><div class='line' id='LC358'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">max_rq_in_driver</span><span class="p">;</span></div><div class='line' id='LC359'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">hw_tag_samples</span><span class="p">;</span></div><div class='line' id='LC360'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">hw_tag</span><span class="p">;</span></div><div class='line' id='LC361'><br/></div><div class='line' id='LC362'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">budgets_assigned</span><span class="p">;</span></div><div class='line' id='LC363'><br/></div><div class='line' id='LC364'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">timer_list</span> <span class="n">idle_slice_timer</span><span class="p">;</span></div><div class='line' id='LC365'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">work_struct</span> <span class="n">unplug_work</span><span class="p">;</span></div><div class='line' id='LC366'><br/></div><div class='line' id='LC367'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">active_queue</span><span class="p">;</span></div><div class='line' id='LC368'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_io_cq</span> <span class="o">*</span><span class="n">active_bic</span><span class="p">;</span></div><div class='line' id='LC369'><br/></div><div class='line' id='LC370'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">sector_t</span> <span class="n">last_position</span><span class="p">;</span></div><div class='line' id='LC371'><br/></div><div class='line' id='LC372'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">ktime_t</span> <span class="n">last_budget_start</span><span class="p">;</span></div><div class='line' id='LC373'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">ktime_t</span> <span class="n">last_idling_start</span><span class="p">;</span></div><div class='line' id='LC374'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">peak_rate_samples</span><span class="p">;</span></div><div class='line' id='LC375'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">peak_rate</span><span class="p">;</span></div><div class='line' id='LC376'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">bfq_max_budget</span><span class="p">;</span></div><div class='line' id='LC377'><br/></div><div class='line' id='LC378'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">hlist_head</span> <span class="n">group_list</span><span class="p">;</span></div><div class='line' id='LC379'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">list_head</span> <span class="n">active_list</span><span class="p">;</span></div><div class='line' id='LC380'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">list_head</span> <span class="n">idle_list</span><span class="p">;</span></div><div class='line' id='LC381'><br/></div><div class='line' id='LC382'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_quantum</span><span class="p">;</span></div><div class='line' id='LC383'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_fifo_expire</span><span class="p">[</span><span class="mi">2</span><span class="p">];</span></div><div class='line' id='LC384'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_back_penalty</span><span class="p">;</span></div><div class='line' id='LC385'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_back_max</span><span class="p">;</span></div><div class='line' id='LC386'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_slice_idle</span><span class="p">;</span></div><div class='line' id='LC387'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">bfq_class_idle_last_service</span><span class="p">;</span></div><div class='line' id='LC388'><br/></div><div class='line' id='LC389'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_user_max_budget</span><span class="p">;</span></div><div class='line' id='LC390'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_max_budget_async_rq</span><span class="p">;</span></div><div class='line' id='LC391'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_timeout</span><span class="p">[</span><span class="mi">2</span><span class="p">];</span></div><div class='line' id='LC392'><br/></div><div class='line' id='LC393'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">bool</span> <span class="n">low_latency</span><span class="p">;</span></div><div class='line' id='LC394'><br/></div><div class='line' id='LC395'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* parameters of the low_latency heuristics */</span></div><div class='line' id='LC396'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_raising_coeff</span><span class="p">;</span></div><div class='line' id='LC397'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_raising_max_time</span><span class="p">;</span></div><div class='line' id='LC398'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_raising_rt_max_time</span><span class="p">;</span></div><div class='line' id='LC399'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_raising_min_idle_time</span><span class="p">;</span></div><div class='line' id='LC400'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_raising_min_inter_arr_async</span><span class="p">;</span></div><div class='line' id='LC401'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">bfq_raising_max_softrt_rate</span><span class="p">;</span></div><div class='line' id='LC402'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">u64</span> <span class="n">RT_prod</span><span class="p">;</span></div><div class='line' id='LC403'><br/></div><div class='line' id='LC404'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="n">oom_bfqq</span><span class="p">;</span></div><div class='line' id='LC405'><span class="p">};</span></div><div class='line' id='LC406'><br/></div><div class='line' id='LC407'><span class="k">enum</span> <span class="n">bfqq_state_flags</span> <span class="p">{</span></div><div class='line' id='LC408'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_busy</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* has requests or is under service */</span></div><div class='line' id='LC409'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_wait_request</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* waiting for a request */</span></div><div class='line' id='LC410'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_must_alloc</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* must be allowed rq alloc */</span></div><div class='line' id='LC411'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_fifo_expire</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* FIFO checked in this slice */</span></div><div class='line' id='LC412'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_idle_window</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* slice idling enabled */</span></div><div class='line' id='LC413'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_prio_changed</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* task priority has changed */</span></div><div class='line' id='LC414'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_sync</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* synchronous queue */</span></div><div class='line' id='LC415'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_budget_new</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* no completion with this budget */</span></div><div class='line' id='LC416'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_coop</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* bfqq is shared */</span></div><div class='line' id='LC417'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_split_coop</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* shared bfqq will be splitted */</span></div><div class='line' id='LC418'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_some_coop_idle</span><span class="p">,</span>   <span class="cm">/* some cooperator is inactive */</span></div><div class='line' id='LC419'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_FLAG_just_split</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* queue has just been split */</span></div><div class='line' id='LC420'><span class="p">};</span></div><div class='line' id='LC421'><br/></div><div class='line' id='LC422'><span class="cp">#define BFQ_BFQQ_FNS(name)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC423'><span class="cp">static inline void bfq_mark_bfqq_##name(struct bfq_queue *bfqq)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC424'><span class="cp">{&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC425'><span class="cp">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(bfqq)-&gt;flags |= (1 &lt;&lt; BFQ_BFQQ_FLAG_##name);&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC426'><span class="cp">}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC427'><span class="cp">static inline void bfq_clear_bfqq_##name(struct bfq_queue *bfqq)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC428'><span class="cp">{&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC429'><span class="cp">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(bfqq)-&gt;flags &amp;= ~(1 &lt;&lt; BFQ_BFQQ_FLAG_##name);&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC430'><span class="cp">}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC431'><span class="cp">static inline int bfq_bfqq_##name(const struct bfq_queue *bfqq)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC432'><span class="cp">{&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC433'><span class="cp">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return ((bfqq)-&gt;flags &amp; (1 &lt;&lt; BFQ_BFQQ_FLAG_##name)) != 0;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\</span></div><div class='line' id='LC434'><span class="cp">}</span></div><div class='line' id='LC435'><br/></div><div class='line' id='LC436'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">busy</span><span class="p">);</span></div><div class='line' id='LC437'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">wait_request</span><span class="p">);</span></div><div class='line' id='LC438'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">must_alloc</span><span class="p">);</span></div><div class='line' id='LC439'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">fifo_expire</span><span class="p">);</span></div><div class='line' id='LC440'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">idle_window</span><span class="p">);</span></div><div class='line' id='LC441'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">prio_changed</span><span class="p">);</span></div><div class='line' id='LC442'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">sync</span><span class="p">);</span></div><div class='line' id='LC443'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">budget_new</span><span class="p">);</span></div><div class='line' id='LC444'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">coop</span><span class="p">);</span></div><div class='line' id='LC445'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">split_coop</span><span class="p">);</span></div><div class='line' id='LC446'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">some_coop_idle</span><span class="p">);</span></div><div class='line' id='LC447'><span class="n">BFQ_BFQQ_FNS</span><span class="p">(</span><span class="n">just_split</span><span class="p">);</span></div><div class='line' id='LC448'><span class="cp">#undef BFQ_BFQQ_FNS</span></div><div class='line' id='LC449'><br/></div><div class='line' id='LC450'><span class="cm">/* Logging facilities. */</span></div><div class='line' id='LC451'><span class="cp">#define bfq_log_bfqq(bfqd, bfqq, fmt, args...) \</span></div><div class='line' id='LC452'><span class="cp">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;blk_add_trace_msg((bfqd)-&gt;queue, &quot;bfq%d &quot; fmt, (bfqq)-&gt;pid, ##args)</span></div><div class='line' id='LC453'><br/></div><div class='line' id='LC454'><span class="cp">#define bfq_log(bfqd, fmt, args...) \</span></div><div class='line' id='LC455'><span class="cp">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;blk_add_trace_msg((bfqd)-&gt;queue, &quot;bfq &quot; fmt, ##args)</span></div><div class='line' id='LC456'><br/></div><div class='line' id='LC457'><span class="cm">/* Expiration reasons. */</span></div><div class='line' id='LC458'><span class="k">enum</span> <span class="n">bfqq_expiration</span> <span class="p">{</span></div><div class='line' id='LC459'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_TOO_IDLE</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* queue has been idling for too long */</span></div><div class='line' id='LC460'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_BUDGET_TIMEOUT</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* budget took too long to be used */</span></div><div class='line' id='LC461'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_BUDGET_EXHAUSTED</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* budget consumed */</span></div><div class='line' id='LC462'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BFQ_BFQQ_NO_MORE_REQUESTS</span><span class="p">,</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* the queue has no more requests */</span></div><div class='line' id='LC463'><span class="p">};</span></div><div class='line' id='LC464'><br/></div><div class='line' id='LC465'><span class="cp">#ifdef CONFIG_CGROUP_BFQIO</span></div><div class='line' id='LC466'><span class="cm">/**</span></div><div class='line' id='LC467'><span class="cm"> * struct bfq_group - per (device, cgroup) data structure.</span></div><div class='line' id='LC468'><span class="cm"> * @entity: schedulable entity to insert into the parent group sched_data.</span></div><div class='line' id='LC469'><span class="cm"> * @sched_data: own sched_data, to contain child entities (they may be</span></div><div class='line' id='LC470'><span class="cm"> *              both bfq_queues and bfq_groups).</span></div><div class='line' id='LC471'><span class="cm"> * @group_node: node to be inserted into the bfqio_cgroup-&gt;group_data</span></div><div class='line' id='LC472'><span class="cm"> *              list of the containing cgroup&#39;s bfqio_cgroup.</span></div><div class='line' id='LC473'><span class="cm"> * @bfqd_node: node to be inserted into the @bfqd-&gt;group_list list</span></div><div class='line' id='LC474'><span class="cm"> *             of the groups active on the same device; used for cleanup.</span></div><div class='line' id='LC475'><span class="cm"> * @bfqd: the bfq_data for the device this group acts upon.</span></div><div class='line' id='LC476'><span class="cm"> * @async_bfqq: array of async queues for all the tasks belonging to</span></div><div class='line' id='LC477'><span class="cm"> *              the group, one queue per ioprio value per ioprio_class,</span></div><div class='line' id='LC478'><span class="cm"> *              except for the idle class that has only one queue.</span></div><div class='line' id='LC479'><span class="cm"> * @async_idle_bfqq: async queue for the idle class (ioprio is ignored).</span></div><div class='line' id='LC480'><span class="cm"> * @my_entity: pointer to @entity, %NULL for the toplevel group; used</span></div><div class='line' id='LC481'><span class="cm"> *             to avoid too many special cases during group creation/migration.</span></div><div class='line' id='LC482'><span class="cm"> *</span></div><div class='line' id='LC483'><span class="cm"> * Each (device, cgroup) pair has its own bfq_group, i.e., for each cgroup</span></div><div class='line' id='LC484'><span class="cm"> * there is a set of bfq_groups, each one collecting the lower-level</span></div><div class='line' id='LC485'><span class="cm"> * entities belonging to the group that are acting on the same device.</span></div><div class='line' id='LC486'><span class="cm"> *</span></div><div class='line' id='LC487'><span class="cm"> * Locking works as follows:</span></div><div class='line' id='LC488'><span class="cm"> *    o @group_node is protected by the bfqio_cgroup lock, and is accessed</span></div><div class='line' id='LC489'><span class="cm"> *      via RCU from its readers.</span></div><div class='line' id='LC490'><span class="cm"> *    o @bfqd is protected by the queue lock, RCU is used to access it</span></div><div class='line' id='LC491'><span class="cm"> *      from the readers.</span></div><div class='line' id='LC492'><span class="cm"> *    o All the other fields are protected by the @bfqd queue lock.</span></div><div class='line' id='LC493'><span class="cm"> */</span></div><div class='line' id='LC494'><span class="k">struct</span> <span class="n">bfq_group</span> <span class="p">{</span></div><div class='line' id='LC495'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_entity</span> <span class="n">entity</span><span class="p">;</span></div><div class='line' id='LC496'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_sched_data</span> <span class="n">sched_data</span><span class="p">;</span></div><div class='line' id='LC497'><br/></div><div class='line' id='LC498'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">hlist_node</span> <span class="n">group_node</span><span class="p">;</span></div><div class='line' id='LC499'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">hlist_node</span> <span class="n">bfqd_node</span><span class="p">;</span></div><div class='line' id='LC500'><br/></div><div class='line' id='LC501'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">void</span> <span class="o">*</span><span class="n">bfqd</span><span class="p">;</span></div><div class='line' id='LC502'><br/></div><div class='line' id='LC503'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">async_bfqq</span><span class="p">[</span><span class="mi">2</span><span class="p">][</span><span class="n">IOPRIO_BE_NR</span><span class="p">];</span></div><div class='line' id='LC504'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">async_idle_bfqq</span><span class="p">;</span></div><div class='line' id='LC505'><br/></div><div class='line' id='LC506'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_entity</span> <span class="o">*</span><span class="n">my_entity</span><span class="p">;</span></div><div class='line' id='LC507'><span class="p">};</span></div><div class='line' id='LC508'><br/></div><div class='line' id='LC509'><span class="cm">/**</span></div><div class='line' id='LC510'><span class="cm"> * struct bfqio_cgroup - bfq cgroup data structure.</span></div><div class='line' id='LC511'><span class="cm"> * @css: subsystem state for bfq in the containing cgroup.</span></div><div class='line' id='LC512'><span class="cm"> * @weight: cgroup weight.</span></div><div class='line' id='LC513'><span class="cm"> * @ioprio: cgroup ioprio.</span></div><div class='line' id='LC514'><span class="cm"> * @ioprio_class: cgroup ioprio_class.</span></div><div class='line' id='LC515'><span class="cm"> * @lock: spinlock that protects @ioprio, @ioprio_class and @group_data.</span></div><div class='line' id='LC516'><span class="cm"> * @group_data: list containing the bfq_group belonging to this cgroup.</span></div><div class='line' id='LC517'><span class="cm"> *</span></div><div class='line' id='LC518'><span class="cm"> * @group_data is accessed using RCU, with @lock protecting the updates,</span></div><div class='line' id='LC519'><span class="cm"> * @ioprio and @ioprio_class are protected by @lock.</span></div><div class='line' id='LC520'><span class="cm"> */</span></div><div class='line' id='LC521'><span class="k">struct</span> <span class="n">bfqio_cgroup</span> <span class="p">{</span></div><div class='line' id='LC522'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">cgroup_subsys_state</span> <span class="n">css</span><span class="p">;</span></div><div class='line' id='LC523'><br/></div><div class='line' id='LC524'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">short</span> <span class="n">weight</span><span class="p">,</span> <span class="n">ioprio</span><span class="p">,</span> <span class="n">ioprio_class</span><span class="p">;</span></div><div class='line' id='LC525'><br/></div><div class='line' id='LC526'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">spinlock_t</span> <span class="n">lock</span><span class="p">;</span></div><div class='line' id='LC527'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">hlist_head</span> <span class="n">group_data</span><span class="p">;</span></div><div class='line' id='LC528'><span class="p">};</span></div><div class='line' id='LC529'><span class="cp">#else</span></div><div class='line' id='LC530'><span class="k">struct</span> <span class="n">bfq_group</span> <span class="p">{</span></div><div class='line' id='LC531'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_sched_data</span> <span class="n">sched_data</span><span class="p">;</span></div><div class='line' id='LC532'><br/></div><div class='line' id='LC533'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">async_bfqq</span><span class="p">[</span><span class="mi">2</span><span class="p">][</span><span class="n">IOPRIO_BE_NR</span><span class="p">];</span></div><div class='line' id='LC534'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">async_idle_bfqq</span><span class="p">;</span></div><div class='line' id='LC535'><span class="p">};</span></div><div class='line' id='LC536'><span class="cp">#endif</span></div><div class='line' id='LC537'><br/></div><div class='line' id='LC538'><span class="k">static</span> <span class="kr">inline</span> <span class="k">struct</span> <span class="n">bfq_service_tree</span> <span class="o">*</span></div><div class='line' id='LC539'><span class="nf">bfq_entity_service_tree</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_entity</span> <span class="o">*</span><span class="n">entity</span><span class="p">)</span></div><div class='line' id='LC540'><span class="p">{</span></div><div class='line' id='LC541'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_sched_data</span> <span class="o">*</span><span class="n">sched_data</span> <span class="o">=</span> <span class="n">entity</span><span class="o">-&gt;</span><span class="n">sched_data</span><span class="p">;</span></div><div class='line' id='LC542'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">idx</span> <span class="o">=</span> <span class="n">entity</span><span class="o">-&gt;</span><span class="n">ioprio_class</span> <span class="o">-</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC543'><br/></div><div class='line' id='LC544'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BUG_ON</span><span class="p">(</span><span class="n">idx</span> <span class="o">&gt;=</span> <span class="n">BFQ_IOPRIO_CLASSES</span><span class="p">);</span></div><div class='line' id='LC545'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">BUG_ON</span><span class="p">(</span><span class="n">sched_data</span> <span class="o">==</span> <span class="nb">NULL</span><span class="p">);</span></div><div class='line' id='LC546'><br/></div><div class='line' id='LC547'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">sched_data</span><span class="o">-&gt;</span><span class="n">service_tree</span> <span class="o">+</span> <span class="n">idx</span><span class="p">;</span></div><div class='line' id='LC548'><span class="p">}</span></div><div class='line' id='LC549'><br/></div><div class='line' id='LC550'><span class="k">static</span> <span class="kr">inline</span> <span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="nf">bic_to_bfqq</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_io_cq</span> <span class="o">*</span><span class="n">bic</span><span class="p">,</span></div><div class='line' id='LC551'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    <span class="kt">int</span> <span class="n">is_sync</span><span class="p">)</span></div><div class='line' id='LC552'><span class="p">{</span></div><div class='line' id='LC553'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">bic</span><span class="o">-&gt;</span><span class="n">bfqq</span><span class="p">[</span><span class="o">!!</span><span class="n">is_sync</span><span class="p">];</span></div><div class='line' id='LC554'><span class="p">}</span></div><div class='line' id='LC555'><br/></div><div class='line' id='LC556'><span class="k">static</span> <span class="kr">inline</span> <span class="kt">void</span> <span class="nf">bic_set_bfqq</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_io_cq</span> <span class="o">*</span><span class="n">bic</span><span class="p">,</span></div><div class='line' id='LC557'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">bfqq</span><span class="p">,</span> <span class="kt">int</span> <span class="n">is_sync</span><span class="p">)</span></div><div class='line' id='LC558'><span class="p">{</span></div><div class='line' id='LC559'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">bic</span><span class="o">-&gt;</span><span class="n">bfqq</span><span class="p">[</span><span class="o">!!</span><span class="n">is_sync</span><span class="p">]</span> <span class="o">=</span> <span class="n">bfqq</span><span class="p">;</span></div><div class='line' id='LC560'><span class="p">}</span></div><div class='line' id='LC561'><br/></div><div class='line' id='LC562'><span class="k">static</span> <span class="kr">inline</span> <span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">*</span><span class="nf">bic_to_bfqd</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_io_cq</span> <span class="o">*</span><span class="n">bic</span><span class="p">)</span></div><div class='line' id='LC563'><span class="p">{</span></div><div class='line' id='LC564'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">bic</span><span class="o">-&gt;</span><span class="n">icq</span><span class="p">.</span><span class="n">q</span><span class="o">-&gt;</span><span class="n">elevator</span><span class="o">-&gt;</span><span class="n">elevator_data</span><span class="p">;</span></div><div class='line' id='LC565'><span class="p">}</span></div><div class='line' id='LC566'><br/></div><div class='line' id='LC567'><span class="cm">/**</span></div><div class='line' id='LC568'><span class="cm"> * bfq_get_bfqd_locked - get a lock to a bfqd using a RCU protected pointer.</span></div><div class='line' id='LC569'><span class="cm"> * @ptr: a pointer to a bfqd.</span></div><div class='line' id='LC570'><span class="cm"> * @flags: storage for the flags to be saved.</span></div><div class='line' id='LC571'><span class="cm"> *</span></div><div class='line' id='LC572'><span class="cm"> * This function allows bfqg-&gt;bfqd to be protected by the</span></div><div class='line' id='LC573'><span class="cm"> * queue lock of the bfqd they reference; the pointer is dereferenced</span></div><div class='line' id='LC574'><span class="cm"> * under RCU, so the storage for bfqd is assured to be safe as long</span></div><div class='line' id='LC575'><span class="cm"> * as the RCU read side critical section does not end.  After the</span></div><div class='line' id='LC576'><span class="cm"> * bfqd-&gt;queue-&gt;queue_lock is taken the pointer is rechecked, to be</span></div><div class='line' id='LC577'><span class="cm"> * sure that no other writer accessed it.  If we raced with a writer,</span></div><div class='line' id='LC578'><span class="cm"> * the function returns NULL, with the queue unlocked, otherwise it</span></div><div class='line' id='LC579'><span class="cm"> * returns the dereferenced pointer, with the queue locked.</span></div><div class='line' id='LC580'><span class="cm"> */</span></div><div class='line' id='LC581'><span class="k">static</span> <span class="kr">inline</span> <span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">*</span><span class="nf">bfq_get_bfqd_locked</span><span class="p">(</span><span class="kt">void</span> <span class="o">**</span><span class="n">ptr</span><span class="p">,</span></div><div class='line' id='LC582'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   <span class="kt">unsigned</span> <span class="kt">long</span> <span class="o">*</span><span class="n">flags</span><span class="p">)</span></div><div class='line' id='LC583'><span class="p">{</span></div><div class='line' id='LC584'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">*</span><span class="n">bfqd</span><span class="p">;</span></div><div class='line' id='LC585'><br/></div><div class='line' id='LC586'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">rcu_read_lock</span><span class="p">();</span></div><div class='line' id='LC587'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">bfqd</span> <span class="o">=</span> <span class="n">rcu_dereference</span><span class="p">(</span><span class="o">*</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">**</span><span class="p">)</span><span class="n">ptr</span><span class="p">);</span></div><div class='line' id='LC588'><br/></div><div class='line' id='LC589'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">bfqd</span> <span class="o">!=</span> <span class="nb">NULL</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC590'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">spin_lock_irqsave</span><span class="p">(</span><span class="n">bfqd</span><span class="o">-&gt;</span><span class="n">queue</span><span class="o">-&gt;</span><span class="n">queue_lock</span><span class="p">,</span> <span class="o">*</span><span class="n">flags</span><span class="p">);</span></div><div class='line' id='LC591'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="o">*</span><span class="n">ptr</span> <span class="o">==</span> <span class="n">bfqd</span><span class="p">)</span></div><div class='line' id='LC592'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">goto</span> <span class="n">out</span><span class="p">;</span></div><div class='line' id='LC593'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">spin_unlock_irqrestore</span><span class="p">(</span><span class="n">bfqd</span><span class="o">-&gt;</span><span class="n">queue</span><span class="o">-&gt;</span><span class="n">queue_lock</span><span class="p">,</span> <span class="o">*</span><span class="n">flags</span><span class="p">);</span></div><div class='line' id='LC594'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC595'><br/></div><div class='line' id='LC596'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">bfqd</span> <span class="o">=</span> <span class="nb">NULL</span><span class="p">;</span></div><div class='line' id='LC597'><span class="nl">out:</span></div><div class='line' id='LC598'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">rcu_read_unlock</span><span class="p">();</span></div><div class='line' id='LC599'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">bfqd</span><span class="p">;</span></div><div class='line' id='LC600'><span class="p">}</span></div><div class='line' id='LC601'><br/></div><div class='line' id='LC602'><span class="k">static</span> <span class="kr">inline</span> <span class="kt">void</span> <span class="nf">bfq_put_bfqd_unlock</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">*</span><span class="n">bfqd</span><span class="p">,</span></div><div class='line' id='LC603'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       <span class="kt">unsigned</span> <span class="kt">long</span> <span class="o">*</span><span class="n">flags</span><span class="p">)</span></div><div class='line' id='LC604'><span class="p">{</span></div><div class='line' id='LC605'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">spin_unlock_irqrestore</span><span class="p">(</span><span class="n">bfqd</span><span class="o">-&gt;</span><span class="n">queue</span><span class="o">-&gt;</span><span class="n">queue_lock</span><span class="p">,</span> <span class="o">*</span><span class="n">flags</span><span class="p">);</span></div><div class='line' id='LC606'><span class="p">}</span></div><div class='line' id='LC607'><br/></div><div class='line' id='LC608'><span class="k">static</span> <span class="kt">void</span> <span class="nf">bfq_changed_ioprio</span><span class="p">(</span><span class="k">struct</span> <span class="n">io_context</span> <span class="o">*</span><span class="n">ioc</span><span class="p">,</span></div><div class='line' id='LC609'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       <span class="k">struct</span> <span class="n">bfq_io_cq</span> <span class="o">*</span><span class="n">bic</span><span class="p">);</span></div><div class='line' id='LC610'><span class="k">static</span> <span class="kt">void</span> <span class="nf">bfq_put_queue</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">bfqq</span><span class="p">);</span></div><div class='line' id='LC611'><span class="k">static</span> <span class="kt">void</span> <span class="nf">bfq_dispatch_insert</span><span class="p">(</span><span class="k">struct</span> <span class="n">request_queue</span> <span class="o">*</span><span class="n">q</span><span class="p">,</span> <span class="k">struct</span> <span class="n">request</span> <span class="o">*</span><span class="n">rq</span><span class="p">);</span></div><div class='line' id='LC612'><span class="k">static</span> <span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="nf">bfq_get_queue</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">*</span><span class="n">bfqd</span><span class="p">,</span></div><div class='line' id='LC613'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       <span class="k">struct</span> <span class="n">bfq_group</span> <span class="o">*</span><span class="n">bfqg</span><span class="p">,</span> <span class="kt">int</span> <span class="n">is_sync</span><span class="p">,</span></div><div class='line' id='LC614'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;       <span class="k">struct</span> <span class="n">io_context</span> <span class="o">*</span><span class="n">ioc</span><span class="p">,</span> <span class="kt">gfp_t</span> <span class="n">gfp_mask</span><span class="p">);</span></div><div class='line' id='LC615'><span class="k">static</span> <span class="kt">void</span> <span class="nf">bfq_put_async_queues</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">*</span><span class="n">bfqd</span><span class="p">,</span> <span class="k">struct</span> <span class="n">bfq_group</span> <span class="o">*</span><span class="n">bfqg</span><span class="p">);</span></div><div class='line' id='LC616'><span class="k">static</span> <span class="kt">void</span> <span class="nf">bfq_exit_bfqq</span><span class="p">(</span><span class="k">struct</span> <span class="n">bfq_data</span> <span class="o">*</span><span class="n">bfqd</span><span class="p">,</span> <span class="k">struct</span> <span class="n">bfq_queue</span> <span class="o">*</span><span class="n">bfqq</span><span class="p">);</span></div><div class='line' id='LC617'><span class="cp">#endif</span></div></pre></div>
            </td>
          </tr>
        </table>
  </div>

  </div>
</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" class="js-jump-to-line-form">
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="button">Go</button>
  </form>
</div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer">
    <ul class="site-footer-links right">
      <li><a href="https://status.github.com/">Status</a></li>
      <li><a href="http://developer.github.com">API</a></li>
      <li><a href="http://training.github.com">Training</a></li>
      <li><a href="http://shop.github.com">Shop</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/about">About</a></li>

    </ul>

    <a href="/">
      <span class="mega-octicon octicon-mark-github"></span>
    </a>

    <ul class="site-footer-links">
      <li>&copy; 2014 <span title="0.09629s from github-fe126-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="/site/terms">Terms</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
        <li><a href="/contact">Contact</a></li>
    </ul>
  </div><!-- /.site-footer -->
</div><!-- /.container -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
          <div class="suggester-container">
              <div class="suggester fullscreen-suggester js-navigation-container" id="fullscreen_suggester"
                 data-url="/bindassdost/Bindass-Boost-a110-JB-Kernel-mt6577/suggestions/commit">
              </div>
          </div>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped leftwards" title="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped leftwards"
      title="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-remove-close close ajax-error-dismiss"></a>
      Something went wrong with that request. Please try again.
    </div>

  </body>
</html>

